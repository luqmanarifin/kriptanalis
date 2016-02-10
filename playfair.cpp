#include <bits/stdc++.h>

using namespace std;

const int SIZE_CHAR_PER_WORD = 5;
const int SIZE_WORD_PER_LINE = 5;

bool isAlpha(char c) {
  return 'A' <= c && c <= 'Z';
}

string clear_whitespace(string str) {
  string ret;
  for(int i = 0; i < str.length(); i++) {
    if(isAlpha(str[i])) {
      ret.push_back(str[i]);
    }
  }
  return ret;
}

string encrypt(string plain, vector<string> key) {
  vector<int> temp;
  for(int i = 0; i < plain.size(); i++) {
    if(plain[i] == 'J') {
      plain[i] = 'I';
    }
  }
  for(int i = 0; i < plain.size(); i++) {
    if(i + 1 < plain.size() && plain[i] == plain[i + 1] && temp.size() % 2 == 0) {
      temp.push_back(plain[i] - 'A');
      temp.push_back(25);
      temp.push_back(plain[++i] - 'A');
    } else {
      temp.push_back(plain[i] - 'A');
    }
  }
  if(temp.size() % 2) {
    temp.push_back(25);
  }

  int a[26], b[26];
  for(int i = 0; i < key.size(); i++) {
    for(int j = 0; j < key[i].size(); j++) {
      a[key[i][j] - 'A'] = i;
      b[key[i][j] - 'A'] = j;
    }
  }
  string ret;

  for(int i = 0; i < temp.size(); i += 2) {
    if(a[temp[i]] == a[temp[i + 1]]) {
      
      assert(b[temp[i]] != b[temp[i + 1]]);
      ret.push_back(key[a[temp[i]]][(b[temp[i]] + 1) % 5]);
      ret.push_back(key[a[temp[i+1]]][(b[temp[i+1]] + 1) % 5]);

    } else if(b[temp[i]] == b[temp[i + 1]]) {

      ret.push_back(key[(a[temp[i]] + 1) % 5][b[temp[i]]]);
      ret.push_back(key[(a[temp[i+1]] + 1) % 5][b[temp[i+1]]]);

    } else {

      ret.push_back(key[a[temp[i]]][b[temp[i + 1]]]);
      ret.push_back(key[a[temp[i + 1]]][b[temp[i]]]);

    }
  }
  return ret;
}

string decrypt(string cipher, vector<string> key) {
  vector<int> temp;
  for(int i = 0; i < cipher.size(); i++) {
    temp.push_back(cipher[i] - 'A');
  }
  int a[26], b[26];
  for(int i = 0; i < key.size(); i++) {
    for(int j = 0; j < key[i].size(); j++) {
      a[key[i][j] - 'A'] = i;
      b[key[i][j] - 'A'] = j;
    }
  }

  string ret;
  for(int i = 0; i < temp.size(); i += 2) {
    if(a[temp[i]] == a[temp[i + 1]]) {

      assert(b[temp[i]] != b[temp[i + 1]]);
      ret.push_back(key[a[temp[i]]][(b[temp[i]] + 4) % 5]);
      ret.push_back(key[a[temp[i+1]]][(b[temp[i+1]] + 4) % 5]);

    } else if(b[temp[i]] == b[temp[i + 1]]) {

      ret.push_back(key[(a[temp[i]] + 4) % 5][b[temp[i]]]);
      ret.push_back(key[(a[temp[i+1]] + 4) % 5][b[temp[i+1]]]);

    } else {

      ret.push_back(key[a[temp[i]]][b[temp[i + 1]]]);
      ret.push_back(key[a[temp[i + 1]]][b[temp[i]]]);

    }
  }
  return ret;
}

string read_text(int argc, char** argv, string type) {
  string str;
  if(argc == 2) {
    cout << "Enter " << type << " text:" << endl;
    getline(cin, str);
  } else {
    ifstream file(argv[2]);
    string buf;
    while(getline(file, buf)) {
      str += buf;
    }
  }
  return str;
}

vector<string> read_key() {
  string key;
  cout << "Enter key: (masukkan 25 alphabet unique tanpa J):" << endl;
  cout << "Berbentuk dengan 5x5" << endl;
  vector<string> ret;
  for(int i = 0; i < 5; i++) {
    getline(cin, key);
    ret.push_back(key);
  }
  return ret;
}

void string_cleansing(string& str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  str = clear_whitespace(str);
}

void print_result(string type, string result) {
  cout << endl << type << " text:" << endl;
  for(int i = 0; i < result.length(); i++) {
    if(i % SIZE_CHAR_PER_WORD == 0) {
      cout << " ";
    }
    if(i % (SIZE_CHAR_PER_WORD * SIZE_WORD_PER_LINE) == 0) {
      cout << endl;
    }
    cout << result[i];
  }
  cout << endl;
}

void flush_to_file(string output) {
  string name;
  cout << "Enter name file: ";
  getline(cin, name);
  ofstream file;
  file.open(name.c_str());
  for(int i = 0; i < output.length(); i++) {
    if(i % SIZE_CHAR_PER_WORD == 0) {
      file << " ";
    }
    if(i % (SIZE_CHAR_PER_WORD * SIZE_WORD_PER_LINE) == 0) {
      file << endl;
    }
    file << output[i];
  }
  file << endl;
}

int main(int argc, char** argv) {
  if(argc > 3) {
    cout << "Usage : playfair [encrypt / decrypt] [file_name.in])" << endl;
    cout << "File name [OPTIONAL]" << endl;
    return 0;
  }

  string str;
  vector<string> key;

  if(strcmp(argv[1], "encrypt") == 0) { 
    str = read_text(argc, argv, "plain");
    key = read_key();
    string_cleansing(str);
    for(auto it : key) string_cleansing(it);
    string cipher = encrypt(str, key);
    print_result("cipher", cipher);
    flush_to_file(cipher);
  } else {
    str = read_text(argc, argv, "cipher");
    key = read_key();
    string_cleansing(str);
    for(auto it : key) string_cleansing(it);
    string plain = decrypt(str, key);
    print_result("plain", plain);
    flush_to_file(plain);
  }
  return 0;
}
