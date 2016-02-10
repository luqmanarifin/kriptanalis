#include <bits/stdc++.h>

using namespace std;

const int LEN = 9;

string str, buf;

int cnt[LEN][26];
int key[LEN];

int main() {
  memset(key, -1, sizeof(key));
  while(cin >> buf) {
    str += buf;
  }
  for(int i = 0; i < str.size(); i++) {
    cnt[str[i] - 'A'][i % 6]++;
  }
  for(int i = 0; i < LEN; i++) {
    int best = -1, p = -1;
    for(int j = 0; j < 26; j++) {
      if(cnt[i][j] > best) {
        best = cnt[i][j];
        p = j;
      }
    }
    vector<pair<int, int>> pr;
    for(int j = 0; j < 26; j++) {
      if(cnt[i][j] > 0) {
        pr.emplace_back(cnt[i][j], j);
      }
    }
    sort(pr.begin(), pr.end());
    reverse(pr.begin(), pr.end());
    if(pr.size() > 1) {
      //if(pr[1].first*12 <= pr[0].first*9) {
        if((pr[0].second + 15) % 26 == pr[1].second) {
          printf("%d key found\n", i);
        }
      //}
    }
  }
  return 0;
}