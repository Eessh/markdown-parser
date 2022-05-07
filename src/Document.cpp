#include "../include/Document.h"

Document::Document(const string& filePath) {
  ifstream file(filePath);
  if (file.is_open()) {
    char c;
    while (file.good()) {
      c = file.get();
      _text.push_back(c);
    }
  }
  file.close();
}
Document::Document(const vector <string> &lines) {
  for (const string &line: lines) {
    _text.append(line);
    _text.push_back('\n');
  }
}