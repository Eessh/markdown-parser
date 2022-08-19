#include "../../MarkdownParser.hpp"

int main() {
  std::string markdown;
  std::cin >> markdown;

  Lexer lexer;
  std::vector<Token> tokens = lexer.parseToTokens(markdown);
  
  for (const Token& token: tokens)
    token.log();
  
  AST ast;
  ast.load(tokens);
  
  return 0;
}