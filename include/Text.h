#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Text {
  private:
  vector <string> _text;

  public:
  Text();
  Text(const vector <string> &lines);

  void pushLine(const string &line);

  void print();
};