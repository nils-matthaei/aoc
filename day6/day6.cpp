#include <cstdint>
#include <cstdio>
#include <regex>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

std::vector<uint32_t> extract_nums(std::string str) {
  std::vector<uint32_t> vec;
  
  std::regex pattern("[0-9]+");
  std::sregex_iterator iter(str.begin(), str.end(), pattern);
  std::sregex_iterator end;

  while (iter!=end){
    vec.push_back(std::stoi(iter->str()));
    ++iter;
  }

  return vec;
}

uint32_t beatmedaddy(uint32_t time, uint32_t record) {
  uint32_t times_beaten = 0;
  for (uint32_t i = 0;i<=time ;i++ ) {
    uint32_t dist = i*(time-i);
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
  
  std::vector<uint32_t> times = extract_nums(str_times);
  std::vector<uint32_t> distances = extract_nums(str_dist);

  uint32_t result = 1;
  for(uint32_t i = 0; i<times.size(); i++){
    result *= beatmedaddy(times[i], distances[i]);
  }

  printf("%d\n",result);
  
  return 0;
}