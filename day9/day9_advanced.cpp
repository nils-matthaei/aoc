#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


long get_next(vector<long> sequence){
  bool zeroes = true;
  vector<long> diffs;
  for (int i = 0; i < (int)(sequence.size()-1); i++) {
    long diff = sequence[i+1]-sequence[i];
    printf("%ld ",diff);
    diffs.push_back(diff);
    zeroes = diff != 0 ? false : zeroes;
  }
  printf("\n");
  if(!zeroes){
    return sequence.front() -  get_next(diffs);
  }else{
    return sequence.front() - 0;
  }
}

int main(void){
  fstream infile("input");  
  string buf;

  long res = 0;
  while (getline(infile,buf)){
    stringstream strem(buf);
    vector<long> seq;
    string num;
    while (getline(strem,num, ' ')) {
      seq.push_back(stol(num));
      cout<<num<<" ";
    }
    cout<<"\n";
    res += get_next(seq);
  }
  printf("%ld\n", res);
  return 0;
}