#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class MarkdownDoc {
  public:
  MarkdownDoc();

  void load(const std::string& filepath);
  void log();

  private:
  std::vector<std::string> docData;
};