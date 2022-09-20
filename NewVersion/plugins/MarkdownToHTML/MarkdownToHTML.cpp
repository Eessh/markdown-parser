#include "MarkdownParser.hpp"
#include "Renderer.hpp"

int main(int args, char** argv) {

  std::string filepath="";

  if (args > 1) filepath = argv[1];
  else {
    std::cout << "Expected an argument: path to markdown document.\n";
    std::cout << "Usage: Plugin__Markdown_to_HTML <path to markdown document>\n";
    std::cout << "Example: Plugin__Markdown_to_HTML ./bin/Debug/test.md\n";
    return 0;
  }

  MarkdownParser::MarkdownDoc doc;
  doc.load(filepath);
  doc.log();

  MarkdownParser::Lexer lexer;
  std::vector<MarkdownParser::Token> tokens = lexer.parseDocToTokens(doc);
  
  for (const MarkdownParser::Token& token: tokens)
    token.log();
  std::cout << "\n";
  
  MarkdownParser::AST ast;
  ast.load(tokens);

  Renderer r;
  std::string html = r.render(&ast);
  std::cout << "HTML:\n" << html << "\n";
  
  return 0;
}