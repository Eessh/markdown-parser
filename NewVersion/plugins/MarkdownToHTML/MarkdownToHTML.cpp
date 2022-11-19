#include "MarkdownParser.hpp"
#include "Renderer.hpp"

int main(int args, char** argv) {

  std::string mdFilepath="", htmlFilepath="";

  if (args == 3) {
    mdFilepath = argv[1];
    htmlFilepath = argv[2];
  }
  else {
    std::cout << "Expected 2 arguments: path to markdown document, path to save the generated html.\n";
    std::cout << "Usage: Plugin__Markdown_to_HTML <path to markdown document> <path to save the generated html>\n";
    std::cout << "Example: Plugin__Markdown_to_HTML ./bin/Debug/test.md ./output.html\n";
    return 0;
  }

  MarkdownParser::MarkdownDoc doc;
  doc.load(mdFilepath);
  std::cout << "\nLog: Loading document ...\n";
  // doc.log();
  std::cout << "Log: Document " << mdFilepath << " loaded.\n";

  MarkdownParser::Lexer lexer;
  std::vector<MarkdownParser::Token> tokens = lexer.parseDocToTokens(doc);
  
  // for (const MarkdownParser::Token& token: tokens)
  //   token.log();
  // std::cout << "\n";
  
  MarkdownParser::AST ast;
  ast.load(tokens);

  Renderer r;
  std::string html = r.render(&ast);
  std::cout << "Log: Rendering to HTML ...\n";
  // std::cout << "HTML:\n" << html << "\n";
  std::cout << "Log: Done.\n";

  std::ofstream htmlFile;
  htmlFile.open(htmlFilepath);
  htmlFile << html;
  std::cout << "Log: Saved to " << htmlFilepath << " :)\n\n";
  
  return 0;
}
