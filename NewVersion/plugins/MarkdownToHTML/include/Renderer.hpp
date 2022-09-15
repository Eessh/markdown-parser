#pragma once

#include <iostream>
#include "../MarkdownParser.hpp"

class Renderer {
  public:
  Renderer();

  std::string render(const MarkdownParser::AST* ast);

  private:
  MarkdownParser::ASTNode* iterator;

  std::string recursiveASTRenderer(const MarkdownParser::AST* ast);
};