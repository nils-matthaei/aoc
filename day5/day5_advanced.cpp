#include <cstddef>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

class Range{
  public:
    long dest_start;
    long source_start;
    long length;

    Range(long dest_start, long source_start, long length) : dest_start(dest_start), source_start(source_start), length(length) {}
    explicit Range(std::string range_s) {
      std::regex pattern("[0-9]+");
      std::sregex_iterator iter(range_s.begin(), range_s.end(), pattern);
      std::sregex_iterator end;
      std::vector<long> values;
      
      while (iter!=end){
        values.push_back(std::stol(iter->str()));
        ++iter;
      }
            
        dest_start = values[0];
        source_start = values[1];
        length = values[2];
        std::cout<<"Range "<<values[0]<<" "<<values[1]<<" "<<values[2]<<"\n";
    }
    
};

long in_range(long num, Range &range){
  long source_start = range.source_start;
  long dest_start = range.dest_start;
  long length = range.length;

  if (source_start<=num && num < source_start+length){
    long diff = num - source_start;
    return dest_start +diff;
  }
  return -1;
}

class Farm_Map{
  public:
    std::vector<Range> ranges;  
};

long get_dest(long num, std::vector<Range> &ranges){    
  long dest = -1;
  for (int i = 0; i < ranges.size(); i++) {
    
    if (dest == -1) {
      dest = in_range(num, ranges[i]);
    
    }
  }
  if (dest == -1) {
    dest = num;
  }
  return dest;
}

long calculate_location(std::vector<Farm_Map> &farm, long seed) {
  long location = seed;

  for (Farm_Map map : farm) {
    //std::cout<<"Loc: "<<location<<"\n";
    location = get_dest(location, map.ranges);
  }

  return location;
}

std::vector<long> get_seeds(std::string seed_string) {
  std::regex pattern("[0-9]+");
  std::sregex_iterator iter(seed_string.begin(), seed_string.end(), pattern);
  std::sregex_iterator end;
  std::vector<long> seeds;

  while(iter!=end){
    seeds.push_back(std::stol(iter->str()));
    ++iter;
  }
  return seeds;
}

int main(int argc, char *argv[]){
  std::fstream infile("input.txt");
  std::string buf;
  
  // extract seeds from first line
  std::getline(infile, buf);
  std::vector<long> seeds = get_seeds(buf);
  
  std::vector<Farm_Map> farms;
  
  bool skip = false;
  while (std::getline(infile, buf)){
    
    if (skip) {
      skip = false;
      continue;
    }
    if (buf.length()==0){
      skip = true;
      Farm_Map map;
      farms.push_back(map);
      continue;
    }
    
    Farm_Map *map = &farms.back();
    Range range = Range(buf);
    map->ranges.push_back(range);
  }
  
  long min = -1;
  /*
  for (long seed : seeds) {
    std::cout<<"seed: "<<seed<<" \n";
    long location = calculate_location(farms, seed);
    locations.push_back(location);
  }
  */
  for (int i = 0; i<seeds.size(); i+=2) {
    std::cout<<"i: "<<i<<"\n";
    for (long long j = 0; j<seeds[i+1]; j++) {
      std::cout<<"j: "<<j<<"\n";
      long location = calculate_location(farms, seeds[i]+j);
      if (min == -1){
        min = location;
      }else if (location < min) {
        min = location;
      }
    }
  }

  std::cout<<min<<"\n";
  
  return 0;
}
