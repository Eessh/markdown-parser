#pragma once

#include <string>

typedef enum {
    ROOT,
    HEADING,
    BOLD_ITALIC,
    STRIKETHROUGH,
    CODE,
    QUOTE,
    TEXT,
    NEWLINE
} TokenType;

std::string tokenTypeToStr(const TokenType& type);