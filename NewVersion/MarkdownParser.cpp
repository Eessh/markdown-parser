#include <iostream>
#include "MarkdownDoc.hpp"
#include "Lexer.hpp"
#include "AbstractSyntaxTree.hpp"

int main() {
    std::string s = "#***hola***";
    // std::string s;
    // std::cin >> s;
    MarkdownDoc doc;
    doc.load("C:/Users/Eessh/Documents/projects/markdown-parser/NewVersion/bin/Debug/Test.md");
    doc.log();
    Lexer l;
    std::vector<Token> tokens = l.parseStrToTokens(s);
    for (const Token& t: tokens)
        t.log();
    std::cout << "\n";
    std::vector<Token> docTokens = l.parseDocToTokens(doc);
    for (const Token& t: docTokens)
        t.log();
    
    AST t;
    t.load(tokens);
    return 0;
}