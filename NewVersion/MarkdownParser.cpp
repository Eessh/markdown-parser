#include <iostream>
#include "MarkdownParser.hpp"

int main() {
    // std::string s = "#***hola***";
    std::string s;
    std::cin >> s;
    Lexer l;
    std::vector<Token> tokens = l.parseToTokens(s);
    for (const Token& t: tokens)
        t.log();
    AST t;
    t.load(tokens);
    return 0;
}