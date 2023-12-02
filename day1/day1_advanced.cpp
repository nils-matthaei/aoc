#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, int> digits = {
  {"zero",  0},
  {"one",   1},
  {"two",   2},
  {"three", 3},
  {"four",  4},
  {"five",  5},
  {"six",   6},
  {"seven", 7},
  {"eight", 8},
  {"nine",  9}
};

int get_digit(std::string slice){
  if(digits.find(slice.substr(0,3)) != digits.end()){
    return digits[slice.substr(0,3)];
  }
  
  if(digits.find(slice.substr(0,4)) != digits.end()){
    return digits[slice.substr(0,4)];
  }
  
  if(digits.find(slice.substr(0,5)) != digits.end()){
    return digits[slice.substr(0,5)];
  }

  return -1;
}

int main (int argc, char *argv[]) {
  if (argc<2) {
    std::cout << "Usage: " << argv[0] << " [filename]";
    std::exit(1);
  }
  
  std::fstream infile(argv[1]);
  std::string buf;

  if (!infile.is_open()) {
    std::cout << "Could not open file";
  }

  uint32_t sum = 0;

  while (std::getline(infile, buf)) {
    std::cout << buf << "\n";
    
    uint32_t first_num = -1;
    uint32_t last_num = -1;

    for(int i = 0; i<buf.length(); i++) {
      if (isdigit(buf[i])) {
        uint32_t c_num = buf[i] - 0x30;
        if (first_num == -1) {
          first_num = c_num;
        }
        last_num = c_num;
      }
      else {
        int num = get_digit(buf.substr(i, buf.length()));
        if (num > -1) {
          if (first_num == -1) {
              first_num = num;
          }
          last_num = num;
        }
      }
    }

    std::cout << first_num*10+last_num << "\n";
    sum += first_num*10+last_num; 
  }
 
  infile.close();

  std::cout<< sum;

  return 0;
} 
