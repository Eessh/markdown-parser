#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include "TokenTypes.hpp"

class Token {
    public:
    Token(const TokenType& type);
    Token(const TokenType& type, const unsigned short& level);
    Token(const TokenType& type, const std::string& value);

    TokenType type() const;
    unsigned short level() const;
    std::string value() const;

    bool operator == (const Token& token);

    void log() const;

    private:
    TokenType _type;
    unsigned short _level;
    std::string _value;
};