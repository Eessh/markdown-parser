#include "Token.hpp"

Token::Token(const TokenType& type) {
    if (
        type != ROOT &&
        type != STRIKETHROUGH &&
        type != QUOTE &&
        type != NEWLINE
    ) {
        throw std::runtime_error("Tokens only of type: ROOT, STRIKETHROUGH, QUOTE, NEWLINE can be initialized without value or level.");
    }
    this->_type = type;
}

Token::Token(const TokenType& type, const unsigned short& level) {
    if (
        type != HEADING &&
        type != BOLD_ITALIC &&
        type != CODE
    ) {
        throw std::runtime_error("Tokens only of type: HEADING, BOLD_ITALIC, CODE can be initialized with type and level.");
    }
    this->_type = type;
    this->_level = level;
}

Token::Token(const TokenType& type, const std::string& value) {
    if (type != TEXT) {
        throw std::runtime_error("Token only of type: TEXT can be initalized with type and value.");
    }
    this->_type = type;
    this->_value = value;
}

TokenType Token::type() const {
    return this->_type;
}

unsigned short Token::level() const {
    if (
        this->_type != HEADING &&
        this->_type != BOLD_ITALIC &&
        this->_type != CODE
    ) {
        throw std::runtime_error("Level can only be accessed in tokens of type: HEADING, BOLD_ITALIC, CODE.");
    }
    return this->_level;
}

std::string Token::value() const {
    if (this->_type != TEXT) {
        throw std::runtime_error("Value can only be accessed in token of type: TEXT.");
    }
    return this->_value;
}

bool Token::operator == (const Token& token) {
    if (this->_type == token.type()) {
        switch (this->_type) {
            case TEXT: {
                if (this->_value == token.value()) {
                    return true;
                }
                return false;
            }
            case HEADING:
            case BOLD_ITALIC:
            case CODE: {
                if (this->_level == token.level()) {
                    return true;
                }
                return false;
            }
            default: {
                return true;
            }
        }
    }
    return false;
}

void Token::log() const {
    switch (this->_type) {
        case TEXT:
            std::cout << "<TEXT '" << this->_value << "'>";
            break;
        case HEADING:
            std::cout << "<HEADING " << this->_level << ">";
            break;
        case BOLD_ITALIC:
            std::cout << "<BOLD_ITALIC " << this->_level << ">";
            break;
        case CODE:
            std::cout << "<CODE " << this->_level << ">";
            break;
        case ROOT:
            std::cout << "<ROOT>";
            break;
        case STRIKETHROUGH:
            std::cout << "<STRIKETHROUGH>";
            break;
        case QUOTE:
            std::cout << "<QUOTE>";
            break;
        case NEWLINE:
            std::cout << "<NEWLINE>";
            break;
        default:
            break;
    }
}