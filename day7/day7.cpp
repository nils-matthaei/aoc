#include <cstdint>
#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

int get_rank(string hand) {
  int rank;
  
  regex five_of_a_kind_pattern("([A-Z\\d])\\1{4}");
  regex four_of_a_kind_pattern("([A-Z\\d])\\1{3}[A-Z\\d]\\1");
  regex full_house_pattern("([A-Z\\d])\\1{2}([A-Z\\d])\\2");
  regex three_of_a_kind_pattern("([A-Z\\d])\\1{2}");
  regex two_pair_pattern("([A-Z\\d])\\1([A-Z\\d])\\2[A-Z\\d]|([A-Z\\d])\\3[A-Z\\d]([A-Z\\d])\\4|[A-Z\\d]([A-Z\\d])\\5([A-Z\\d])\\6");
  regex one_pair_pattern("([A-Z\\d])\\1");
  sort(hand.begin(),hand.end());

  if (regex_search(hand,five_of_a_kind_pattern)) {
    rank = 6;
  } else if (regex_search(hand,four_of_a_kind_pattern)) {
    rank = 5;
  } else if (regex_search(hand,full_house_pattern)) {
    rank = 4;
  } else if (regex_search(hand,three_of_a_kind_pattern)) {
    rank = 3;
  } else if (regex_search(hand, two_pair_pattern)) {
    rank = 2;
  } else if (regex_search(hand,one_pair_pattern)) {
    rank = 1;
  } else {
    rank = 0;
  }
  
  return rank;
}

int main(int argc, char *argb[]){
  fstream infile("sample.txt");
  string buf;
  //should have just done a 2d Vector
  vector<pair<string,int>> high_card;
  vector<pair<string,int>> one_pair;
  vector<pair<string,int>> two_pair;
  vector<pair<string,int>> three_of_a_kind;
  vector<pair<string,int>> full_house;
  vector<pair<string,int>> four_of_a_kind;
  vector<pair<string,int>> five_of_a_kind;
  
  while (getline(infile,buf)) {
    string hand = buf.substr(0,5);
    int bid = stoi(buf.substr(6,3));
    int rank = get_rank(hand);

    std::replace(hand.begin(), hand.end(), 'A', 'E');
    std::replace(hand.begin(), hand.end(), 'K', 'D');
    std::replace(hand.begin(), hand.end(), 'Q', 'C');
    std::replace(hand.begin(), hand.end(), 'J', 'B');
    std::replace(hand.begin(), hand.end(), 'T', 'A');
        
    pair<string, int> game(hand,bid);
    switch (rank) {
      case 6:
        five_of_a_kind.push_back(game);
        break;
      case 5:
        four_of_a_kind.push_back(game);
        break;
      case 4:
        full_house.push_back(game);
        break;
      case 3:
        three_of_a_kind.push_back(game);
        break;
      case 2:
        two_pair.push_back(game);
        break;
      case 1:
        one_pair.push_back(game);
        break;
      case 0:
        high_card.push_back(game);
        break;
      default:
        cout<<"oopise\n";
    } 
  }

  //sort the vectors by the hands
  std::vector<std::vector<std::pair<std::string, int>>> all_hands = {high_card, one_pair, two_pair, three_of_a_kind, full_house, four_of_a_kind, five_of_a_kind};
  
  int mult = 1;
  long res;
  for (vector<pair<string, int>> &vec : all_hands){
    std::sort(vec.begin(), vec.end(),
      [](const auto &a, const auto &b) {
          return a.first > b.first;
      });
    for (pair<string,int>game : vec) {
      res += game.second * mult;
      ++mult;
    }
  }

  cout<<res<<"\n";

  return 0;
}