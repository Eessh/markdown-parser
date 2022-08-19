#pragma once

#include <iostream>
#include "../../../MarkdownParser.hpp"

class Renderer {
  public:
  Renderer();

  std::string render(AST* ast);

  private:
  ASTNode* iterator;
};