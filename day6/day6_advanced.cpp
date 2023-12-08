#include <cstdint>
#include <cstdio>
#include <regex>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<long> extract_nums(std::string str) {
  std::vector<long> vec;
  str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
  std::regex pattern("[0-9]+");
  std::sregex_iterator iter(str.begin(), str.end(), pattern);
  std::sregex_iterator end;

  while (iter!=end){
    long num = std::stol(iter->str());
    vec.push_back(num);
    ++iter;
  }

  return vec;
}

long beatmedaddy(long time, long record) {
  long times_beaten = 0;
  for (long i = 0;i<=time ;i++ ) {
    long dist = i*(time-i);
    if (dist>record){
      ++times_beaten;
    }
  }
  return times_beaten;
}

int main(int argc, char *argv[]){
  std::fstream infile("input.txt");
  std::string buf;

  std::getline(infile,buf);
  std::string str_times = buf;
  std::getline(infile,buf);
  std::string str_dist = buf;
  
  std::vector<long> times = extract_nums(str_times);
  std::vector<long> distances = extract_nums(str_dist);
  
  long result = beatmedaddy(times[0], distances[0]);
  
  std::cout<<result<<"\n";
    
  return 0;
}