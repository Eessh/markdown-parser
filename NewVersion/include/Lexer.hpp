#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Token.hpp"

class Lexer {
    public:
    Lexer();

    const std::vector<Token>& parseToTokens(const std::string& source);

    private:
    std::vector<Token> _tokens;
    unsigned long long int _index;

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