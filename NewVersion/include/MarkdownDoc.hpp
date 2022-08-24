#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class MarkdownDoc {
  public:
  std::vector<std::string> docData;
  
  MarkdownDoc();

  void load(const std::string& filepath);
  void log();
};