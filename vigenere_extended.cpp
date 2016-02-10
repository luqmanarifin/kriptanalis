#include <bits/stdc++.h>

using namespace std;

#define byte unsigned char
#define MAX_KEY_LENGTH 30

vector<byte> encrypt(vector<byte> plain, vector<byte> key) {
  vector<byte> cipher(plain.size());
  printf("Encrypting file of size %d bytes.\n", plain.size());
  for(int i = 0; i < plain.size(); i++) {
    cipher[i] = (plain[i] + key[i % key.size()]) % 256;
  }
  return cipher;
}

vector<byte> decrypt(vector<byte> cipher, vector<byte> key) {
  vector<byte> plain(cipher.size());
  printf("Decrypting file of size %d bytes.\n", cipher.size());
  for(int i = 0; i < cipher.size(); i++) {
    plain[i] = (cipher[i] - key[i % key.size()] + 256) % 256;
  }
  return plain;
}

vector<byte> read_text(int argc, char** argv, string type) {
  string str;
  if(argc == 2) {
    cout << "Enter " << type << " text:" << endl;
    getline(cin, str);
  } else {
    ifstream file(argv[2]);
    string buf((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());;
    str = buf;
  }
  vector<byte> ret;
  for(int i = 0; i < str.size(); i++) {
    ret.push_back((byte) str[i]);
  }
  return ret;
}

vector<byte> read_key() {
  string key;
  cout << "Enter key: ";
  getline(cin, key);

  vector<byte> ret;
  for(int i = 0; i < key.size(); i++) {
    ret.push_back(key[i]);
  }
  return ret;
}

void print_result(string type, vector<byte> result) {
  cout << endl << type << " text:" << endl;
  for(int i = 0; i < result.size(); i++) {
    cout << result[i];
  }
  cout << endl;
}

void flush_to_file(vector<byte> output) {
  char* name = new char[MAX_KEY_LENGTH * MAX_KEY_LENGTH];
  cout << "Enter name file: ";
  gets(name);
  ofstream file;
  file.open(name);
  for(int i = 0; i < output.size(); i++) {
    file << output[i];
  }
}

int main(int argc, char** argv) {
  if(argc > 3 || strcmp(argv[0], "ascii")) {
    cout << "Usage : ascii [encrypt / decrypt] [file_name.in])" << endl;
    cout << "File name [OPTIONAL]" << endl;
    return 0;
  }

  vector<byte> str, key;

  if(strcmp(argv[1], "encrypt") == 0) { 
    str = read_text(argc, argv, "plain");
    key = read_key();
    vector<byte> cipher = (vector<byte>) encrypt(str, key);
    print_result("cipher", cipher);
    flush_to_file(cipher);
  } else {
    str = read_text(argc, argv, "cipher");
    key = read_key();
    vector<byte> plain = (vector<byte>) decrypt(str, key);
    print_result("plain", plain);
    flush_to_file(plain);
  }

  return 0;
}
