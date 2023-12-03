#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Gear {
  public:
    uint32_t num;
    uint32_t x;
    uint32_t y;
    size_t len;
    bool found;

   Gear(uint32_t num, uint32_t x, uint32_t y, size_t len, bool found) : num(num), x(x), y(y), len(len), found(found) {}
};

uint32_t get_line_length(std::string input){
  uint32_t length = 0;
  for(int i = 0; i<input.length(); i++){
    ++length;
    if (input[i]=='\n') {
      break;
    }
  }
  return length;
}

void find_gears(std::string machine, std::vector<Gear> &gears){
  uint32_t line_length = get_line_length(machine);
  std::regex pattern("([0-9]+)");
  std::sregex_iterator iter(machine.begin(), machine.end(), pattern);
  std::sregex_iterator end;

  while(iter != end){
    std::smatch match = *iter;

    uint32_t num = std::stoi(match.str());
    uint32_t pos = match.position();
    uint32_t len = match.length();

    uint32_t y = pos/line_length;
    uint32_t x = pos%line_length; 

    Gear gear(num, x, y, len, false);

    gears.push_back(gear);

    // std::cout<<num<<" "<<pos<<" ("<<y<<","<<x<<") "<<gears.size()<<"\n";
    ++iter;
  }
}

uint32_t calculate_part(std::string machine, std::vector<Gear> &gears){
  uint32_t part = 0;
  uint32_t line_length = get_line_length(machine);
  // std::regex pattern("([^0-9\\.\n])");
  std::regex pattern("(\\*)");
  std::sregex_iterator iter(machine.begin(), machine.end(), pattern);
  std::sregex_iterator end;

  while (iter != end) {
    std::smatch symbol = *iter;
    uint32_t pos = symbol.position();
    uint32_t y = pos/line_length;
    uint32_t x = pos%line_length;
    std::vector<uint32_t> hits; 

    for (int dy = -1; dy<2; dy++) {
      for (int dx = -1; dx<2; dx++) {
        uint32_t cy = y+dy;
        uint32_t cx = x+dx;
        for (Gear &gear : gears) {
          if (!gear.found && cy == gear.y && (gear.x <= cx && cx < gear.x+gear.len )) {
            gear.found = true;
            hits.push_back(gear.num);
          } 
        }
      }
    }

    if (hits.size()==2) {
      std::cout<<"Hits: "<<hits[0]<<" "<<hits[1]<<"\n";
      part += hits[0]*hits[1];
    }

    ++iter;
  }
    
  return part;
}

int main(int argc, char* argv[]){
  //File shit
  std::ifstream infile("input3.txt");
  if (!infile.is_open()) {
    std::cout<<"An oopsie happend";
  }
  std::string machine((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
  infile.close();
  
  //
  std::vector<Gear> gears;

  find_gears(machine, gears);

  uint32_t sum = calculate_part(machine, gears);

  std::cout<<sum<<"\n";

  return 0;
}
