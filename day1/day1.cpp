#include <iostream>
#include <string>
#include <fstream>

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

    for (char c : buf) {
      uint32_t c_num = c - 0x30;
      if (isdigit(c)) {
        if (first_num==-1) {
          first_num = c_num;
        }
        last_num = c_num;
      }
    }

    std::cout << first_num*10+last_num << "\n";
    sum += first_num*10+last_num; 
  }
 
  infile.close();

  std::cout<< sum;

  return 0;
} 
