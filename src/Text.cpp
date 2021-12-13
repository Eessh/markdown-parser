#include "../include/Text.h"

Text::Text() {}
Text::Text(const vector <string> &lines) {
  for (const string &line: lines) {
    pushLine(line);
  }
}

void Text::pushLine(const string &line) {
  _text.push_back(line);
  return;
}

void Text::print() {
  cout << "Text: {" << endl;
  for (const string &line: _text) {
    cout << "\t" << line << endl;
  }
  cout << "}" << endl;
}