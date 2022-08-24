#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Token.hpp"
#include "MarkdownDoc.hpp"

class Lexer {
    public:
    Lexer();

    const std::vector<Token>& parseStrToTokens(const std::string& source);
    const std::vector<Token>& parseDocToTokens(const MarkdownDoc& doc);

    private:
    std::vector<Token> _tokens;
    unsigned long long int _index;

    void commonFunc(const std::string& source);

    bool specialChar(const char& c);

    void handleHash(const std::string& source);
    void handleAsterisk(const std::string& source);
    void handleUnderscore(const std::string& source);
    void handleTilda(const std::string& source);
    void handleBacktick(const std::string& source);
    void handleGreater(const std::string& source);
    void handleNewline(const std::string& source);
    void handleText(const std::string& source);
};