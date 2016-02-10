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

string encrypt(string plain, string key) {
  string cipher;
  for(int i = 0; i < plain.length(); i++) {
    int c = (plain[i] - 'A' + key[i % key.length()] - 'A') % 26;
    cipher.push_back(c + 'A');
  }
  return cipher;
}

string decrypt(string cipher, string key) {
  string plain;
  for(int i = 0; i < cipher.length(); i++) {
    int c = (cipher[i] - 'A' - (key[i % key.length()] - 'A') + 26) % 26;
    plain.push_back(c + 'A');
  }
  return plain;
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

string read_key() {
  string key;
  cout << "Enter key: ";
  getline(cin, key);
  return key;
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
    cout << "Usage : vigenere [encrypt / decrypt] [file_name.in])" << endl;
    cout << "File name [OPTIONAL]" << endl;
    return 0;
  }

  string str, key;

  if(strcmp(argv[1], "encrypt") == 0) { 
    str = read_text(argc, argv, "plain");
    key = read_key();
    string_cleansing(str);
    string_cleansing(key);
    string cipher = encrypt(str, key);
    print_result("cipher", cipher);
    flush_to_file(cipher);
  } else {
    str = read_text(argc, argv, "cipher");
    key = read_key();
    string_cleansing(str);
    string_cleansing(key);
    string plain = decrypt(str, key);
    print_result("plain", plain);
    flush_to_file(plain);
  }
  return 0;
}
