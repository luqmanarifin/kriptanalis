#include <bits/stdc++.h>

using namespace std;

string str, buf;

int key[10];
string plain;

void clean() {
  for(int i = 0; i < str.size(); i++) {
    if(key[i % 9] == -1) {
      plain[i] = '*';
    } else {
      plain[i] = (str[i] - 'A' - key[i % 9] + 26) % 26 + 'A';
    }
  }
}

int main() {
  memset(key, -1, sizeof(key));
  while(cin >> buf) {
    str += buf;
  }
  for(int i = 0; i < str.size(); i++) {
    plain.push_back('*');
  }
  key[0] = 11;
  key[1] = 0;
  key[2] = 20;
  key[3] = 19;
  key[4] = 12;
  key[5] = 4;
  key[6] = 17;
  key[7] = 0;
  key[8] = 7;
  clean();
  for(int i = 0; i + 9 <= plain.size(); i += 9) {
    string now = plain.substr(i + 1, 8);
    if(now == "YRAMIDOF") {
      key[0] = (str[i + 0] - 'P' + 26) % 26;
    }
  }
  clean();
  cout << plain << endl;
  for(int i = 0; i < 9; i++) {
    printf("%c", key[i] + 'A');
  }
  return 0;
}