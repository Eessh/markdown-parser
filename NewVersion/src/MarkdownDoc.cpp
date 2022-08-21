#include "MarkdownDoc.hpp"

MarkdownDoc::MarkdownDoc() {};

void MarkdownDoc::load(const std::string& filepath) {
  std::ifstream file;
  file.open(filepath, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  std::string s;
  while (file.good()) {
    std::getline(file, s);
    this->docData.push_back(s);
  }
}

void MarkdownDoc::log() {
  std::cout << "MarkdownDoc:\n";
  for (const std::string& s: this->docData) {
    std::cout << s << "\n";
  }
}