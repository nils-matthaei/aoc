#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

uint32_t calculate_points(std::string card){
  std::regex pattern("([0-9]+|\\|)"); //Match any number or pipe character '|'
  std::sregex_iterator iter(card.begin(), card.end(), pattern);
  std::sregex_iterator end;
  bool pipe = false;
  int exponent = -1;
  std::unordered_map<std::string, bool> winners;

  ++iter; //Skip Card Number

  while (iter!=end) {
    if (iter->str()=="|") {
      pipe = true;
    }

    if (!pipe) {
      winners[iter->str()]=true;
    }else{
      if (winners.find(iter->str())!=winners.end()) {
        ++exponent;
      }
    }
    ++iter;
  }

  if (exponent>-1){
    return 1<<exponent;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  std::ifstream infile("input4.txt");
  if (!infile.is_open()){
    std::cout<<"wo file???"; 
  }
  std::string buf;
  uint32_t total_points = 0;
  
  while (std::getline(infile,buf)) {
    total_points += calculate_points(buf);
  }
  infile.close();

  std::cout<<total_points;
  
  return 0;
}