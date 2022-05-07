#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Document {
  public:
  Document(const string& filePath);
  Document(const vector<string> &lines);

  inline string getText() {return _text;} 

  inline void print() {cout << _text << "\n";}

  private:
  string _text;
};