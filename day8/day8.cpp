#include <unordered_map>
#include <string>
#include <utility>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
  fstream infile("input");
  string buf;
  getline(infile, buf);
  string instructions = buf;

  unordered_map<string, pair<string,string>> network;
  
  while (getline(infile,buf)) {
    if (buf.size()==0) {
      continue;
    }
    string node = buf.substr(0,3);
    string left = buf.substr(7,3);
    string right = buf.substr(12,3);
    pair<string, string> next(left,right);
    network[node] = next;
  }

  int i = 0;
  int count = 0;
  string current = "AAA";
  string end = "ZZZ";

  while (current != end) {
    if (i == instructions.length()) {
      i = 0;
    }
    cout<<current<<" ";
    if (instructions[i]=='L'){
      cout<<"L\n";
      current = network[current].first;
    }else {
      cout<<"R\n";
      current = network[current].second;
    }
    i++;
    count++;
  }

  cout<<count<<"\n";
  
  return 0;
}