#include <bits/stdc++.h>

using namespace std;

string str, buf;

int main(int argc, char** argv) {
  while(cin >> buf) {
    str += buf;
  }
  map<string, int> mp;
  for(int len = 9; len <= 9; len++) {
    for(int i = 0; i + 3 <= str.size(); i++) {
      string sub = str.substr(i, 3);
      if(sub == "KHL") {
        printf("%d\n", i % len);
      }
      mp[sub]++;
    }
  }
  for(auto it : mp) {
    //if(it.second > 5) printf("%s %d\n", it.first.c_str(), it.second);
  }
  return 0;
}