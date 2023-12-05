#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>

class Card {
  public:  
    uint32_t num_copies = 1;
    uint32_t hits;

    Card(uint32_t hits) : hits(hits) {}
};

uint32_t calculate_points(std::string card){
  std::regex pattern("([0-9]+|\\|)"); //Match any number or pipe character '|'
  std::sregex_iterator iter(card.begin(), card.end(), pattern);
  std::sregex_iterator end;
  bool pipe = false;
  int exponent = 0;
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
  
  return exponent;
}

int main(int argc, char *argv[]) {
  std::ifstream infile("input4.txt");
  if (!infile.is_open()){
    std::cout<<"wo file???"; 
  }
  std::string buf;
  uint32_t total_points = 0;
  std::vector<Card> cards;
  while (std::getline(infile,buf)) {
    uint32_t hits = calculate_points(buf);
    Card card = Card(hits);

    cards.push_back(card); 
  }
  infile.close();

  std::cout<<"Loop 3\n";
  for (int i = 0; i < cards.size(); i++) {
    Card card = cards[i];
      for (int j = 1; j <= card.hits; j++) {
        if (i+j<cards.size()){
          cards[i+j].num_copies +=  card.num_copies; 
      } 
    }
    std::cout << "Card: " << i << " copies: " << card.num_copies <<"\n";
    total_points += card.num_copies;
  }

  std::cout<<total_points<<"\n";
  
  return 0;
}
