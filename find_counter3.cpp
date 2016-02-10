#include <bits/stdc++.h>

using namespace std;

map<string, int> cnt;
string buf;

int main() {
  while(cin >> buf) {
    cnt[buf]++;
  }
  vector<pair<int, string>> p;
  for(auto it : cnt) {
    p.emplace_back(it.second, it.first);
  }
  sort(p.begin(), p.end());
  reverse(p.begin(), p.end());
  for(auto it : p) {
    printf("%d %s\n", it.first, it.second.c_str());
  }
  return 0;
}