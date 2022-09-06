#pragma once

#include <iostream>
#include "../MarkdownParser.hpp"

class Renderer {
  public:
  Renderer();

  std::string render(const AST* ast);

  private:
  ASTNode* iterator;

  std::string recursiveASTRenderer(const AST* ast);
};