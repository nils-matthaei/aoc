#include <cstdint>
#include <unordered_map>
#include <string>
#include <utility>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
  fstream infile("sample");
  string buf;
  getline(infile, buf);
  string instructions = buf;

  unordered_map<string, pair<string,string>> network;
  vector<string> start_nodes;  
  while (getline(infile,buf)) {
    if (buf.size()==0) {
      continue;
    }
    string node = buf.substr(0,3);
    string left = buf.substr(7,3);
    string right = buf.substr(12,3);
    pair<string, string> next(left,right);
    network[node] = next;

    if(node[2]=='A'){
      start_nodes.push_back(node);
    }
  }

  int i = 0;
  uint64_t count = 0;
  bool escaped = false;
  
  while (!escaped) {
    if (i == instructions.length()) {
      i = 0;
    }
    escaped = true;
    if (instructions[i]=='L'){
      for(string &node: start_nodes){
        node = network[node].first;
        if (node[2]!='Z'){
          escaped = false;
        }
      }          
    }else {
      for(string &node: start_nodes){
        node = network[node].second;
        if (node[2]!='Z'){
          escaped = false;
        }
      }          
    }
    i++;
    count++;
  }

  cout<<count<<"\n";
  
  return 0;
}