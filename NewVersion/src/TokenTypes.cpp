#include "TokenTypes.hpp"

std::string tokenTypeToStr(const TokenType& type) {
    switch (type) {
        case ROOT:
            return "ROOT";
        case HEADING:
            return "HEADING";
        case BOLD_ITALIC:
            return "BOLD_ITALIC";
        case STRIKETHROUGH:
            return "STRIKETHROUGH";
        case CODE:
            return "CODE";
        case QUOTE:
            return "QUOTE";
        case TEXT:
            return "TEXT";
        default:
            break;
    }
    return "NEWLINE";
}