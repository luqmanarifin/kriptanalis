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

int getFileSize(FILE* file) {
  int l = ftell(file);
  fseek(file, 0, 2);
  int r = ftell(file);
  fseek(file, l, 0);
  return r;
}

vector<byte> read_text(int argc, char** argv) {
  FILE* file = NULL;
  vector<byte> plain;
  assert(file = fopen(argv[2], "rb"));
  int fileSize = getFileSize(file);
  byte* filebuf = new byte[fileSize];
  fread(filebuf, fileSize, 1, file);
  for(int i = 0; i < fileSize; i++) {
    plain.push_back((byte) filebuf[i]);
  }
  return plain;
}

vector<byte> read_key() {
  char* key = new char[MAX_KEY_LENGTH];
  cout << "Enter key: ";
  gets(key);
  int len = strlen(key);
  vector<byte> ret;
  for(int i = 0; i < len; i++) {
    ret.push_back((byte) key[i]);
  }
  return ret;
}

void flush_to_file(vector<byte> output) {
  char* name = new char[MAX_KEY_LENGTH * MAX_KEY_LENGTH];
  cout << "Enter name file: ";
  gets(name);
  cout << printf("Flushing %d bytes to %s\n", output.size(), name);

  FILE* file;
  file = fopen(name, "wb");
  char* buffer = new char[output.size()];
  for(int i = 0; i < output.size(); i++) buffer[i] = output[i];
  fwrite(buffer, sizeof(byte), output.size(), file);
}

int main(int argc, char** argv) {
  if(argc > 3 || strcmp(argv[0], "bonus")) {
    cout << "Usage : bonus [encrypt / decrypt] [file_name.in])" << endl;
    cout << "File name [OPTIONAL]" << endl;
    return 0;
  }

  vector<byte> str, key;

  if(strcmp(argv[1], "encrypt") == 0) { 
    str = read_text(argc, argv);
    key = read_key();
    vector<byte> cipher = (vector<byte>) encrypt(str, key);
    flush_to_file(cipher);
  } else {
    str = read_text(argc, argv);
    key = read_key();
    vector<byte> plain = (vector<byte>) decrypt(str, key);
    flush_to_file(plain);
  }

  return 0;
}
