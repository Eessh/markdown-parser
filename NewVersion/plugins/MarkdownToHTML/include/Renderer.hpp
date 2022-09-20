#pragma once

#include <iostream>
#include "../MarkdownParser.hpp"

class Renderer {
  public:
  Renderer();

  std::string render(const MarkdownParser::AST* ast);

  private:
  MarkdownParser::ASTNode* iterator;

  std::string recursiveASTRenderer(const MarkdownParser::ASTNode* node);
  void handleHeadings(std::string& contentStr, const unsigned short& level);
  void handleBoldItalic(std::string& contentStr, const unsigned short& level);
  void handleCode(std::string& contentStr, const unsigned short& level);
  void handleStrikethrough(std::string& contentStr);
  void handleQuote(std::string& contentStr);
};