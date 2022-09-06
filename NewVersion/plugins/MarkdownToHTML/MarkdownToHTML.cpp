#include "MarkdownParser.hpp"

int main() {
  MarkdownDoc doc;
  // doc.load("C:/Users/Eessh/Documents/projects/markdown-parser/NewVersion/plugins/MarkdownToHTML/bin/Debug/test.md");
  doc.load("C:/Users/Eessh/Documents/projects/markdown-parser/README.md");
  doc.log();

  Lexer lexer;
  std::vector<Token> tokens = lexer.parseDocToTokens(doc);
  
  for (const Token& token: tokens)
    token.log();
  std::cout << "\n";
  
  AST ast;
  ast.load(tokens);
  
  return 0;
}