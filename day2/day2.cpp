#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sys/types.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int max_color(std::string games, std::string color){
  std::regex pattern("([0-9]+) "+ color);
  std::sregex_iterator iter(games.begin(), games.end(), pattern);
  std::sregex_iterator end;

  int max = 0;
  while(iter != end){
    int number = std::stoi(iter->str(1));
    if (max < number) {
      max = number;
    }
    ++iter; 
  }
  return max;
}

bool validgame(std::string games){
  int max_green = max_color(games, "green");
  int max_blue = max_color(games, "blue");
  int max_red = max_color(games, "red");

  if (max_red > MAX_RED || max_green > MAX_GREEN || max_blue > MAX_BLUE) {
    return false;
  }
  return true;
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cout<<"Usage: " << argv[0] << " [filename]";
  }
  
  uint32_t sum = 0;
  std::ifstream infile(argv[1]);
  std::string buf;

  if (!infile.is_open()){
    std::cout<<"an oooopsie wooopsie occured when opening the fiwe";
  }

  while (std::getline(infile,buf)) {
    std::regex pattern("Game ([0-9]+):");
    std::smatch match;
    std::regex_search(buf, match, pattern);
    uint32_t game_number = std::stoi(match.str(1));

    if (validgame(buf)) {
      std::cout<<"Game "<<game_number <<" valid\n";
      sum += game_number;
    }
  }

  infile.close();
  std::cout << sum;
  return 0;
}
