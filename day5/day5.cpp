#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

class Range{
  private:
    long dest_start;
    long source_start;
    long length;

  public:
    Range(long dest_start, long source_start, long length) : dest_start(dest_start), source_start(source_start), length(length) {}

    long in_range(long num){
    if (num >= source_start && num < source_start+length) {
     return dest_start + (num-source_start); 
    }
    return -1;
  } 
};

class Farm_Map{
  public:
    std::vector<Range> ranges;

  long get_dest(long num){
    long dest = -1;
    for (Range range : ranges) {
      if (dest == -1) {
        dest = range.in_range(num);
      }
    }
    if (dest == -1) {
      dest = num;
    }
    return dest;
  }
};

long calculate_location(std::vector<Farm_Map> farm, long seed) {
  long location = seed;

  for (Farm_Map map : farm) {
    location = map.get_dest(seed);
  }

  return location;
}

std::vector<long> get_seeds(std::string seed_string) {
  std::regex pattern("[0-9]+");
  std::sregex_iterator iter(seed_string.begin(), seed_string.end(), pattern);
  std::sregex_iterator end;
  std::vector<long> seeds;

  while(iter!=end){
    seeds.push_back(std::stoi(iter->str()));
  }

  return seeds;
}

int main(int argc, char *argv[]){
  std::fstream infile("sample.txt");
  std::string buf;

  std::regex pattern("[0-9]+");

  // extract seeds from first line
  std::getline(infile, buf);
  std::vector<long> seeds = get_seeds(buf);
  
  std::vector<Farm_Map> farms;
  
  while (std::getline(infile, buf)){
    std::sregex_iterator iter(buf.begin(),buf.end(),pattern);
    std::sregex_iterator end;
    
    if (buf.length()==0){
      
    }
  }
  
  return 0;
}