#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>




/*
 * Declarations
 */
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

class ASTNode {
    public:
    Token token;
    std::vector<ASTNode*> children;

    ASTNode(const Token& token);

    void addChild(ASTNode* child);
    ASTNode* lastInsertedChild();
};

class AST {
    public:
    AST();
    ~AST();
    
    void load(const std::vector<Token>& tokens);

    private:
    ASTNode* _root;
    ASTNode* _iterator;
    std::stack<ASTNode*> _iteratorHistory;
};




/*
 * Definitions
 */
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
                    std::cout << "Log: Returning true\n";
                    return true;
                }
                return false;
            }
            case HEADING:
            case BOLD_ITALIC:
            case CODE: {
                if (this->_level == token.level()) {
                    std::cout << "Log: Returning true\n";
                    return true;
                }
                return false;
            }
            default: {
                std::cout << "Log: Returning true\n";
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

Lexer::Lexer() {
    this->_tokens = std::vector<Token>();
    this->_index = 0;
}

const std::vector<Token>& Lexer::parseToTokens(const std::string& source) {
    this->_tokens.clear();
    this->_index = 0;
    while (this->_index < source.size()) {
        this->handleHash(source);
        this->handleAsterisk(source);
        this->handleUnderscore(source);
        this->handleTilda(source);
        this->handleBacktick(source);
        this->handleGreater(source);
        this->handleNewline(source);
        this->handleText(source);
    }
    return this->_tokens;
}

bool Lexer::specialChar(const char& c) {
    if (
        c == '#' ||
        c == '*' ||
        c == '_' ||
        c == '~' ||
        c == '`' ||
        c == '>' ||
        c == '\n'
    ) {
        return true;
    }
    return false;
}

void Lexer::handleHash(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    unsigned long long length = 0;
    while (this->_index<source.size() && source[this->_index]=='#') {
        length++;
        this->_index++;
    }
    if (length == 0) {
        return;
    }
    if (length > 6) {
        throw std::runtime_error("Headings restricted to only 6 levels.");
    }
    this->_tokens.push_back(Token(HEADING, length));
}

void Lexer::handleAsterisk(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    unsigned long long length = 0;
    while (this->_index<source.size() && source[this->_index]=='*') {
        length++;
        this->_index++;
    }
    if (length == 0) {
        return;
    }
    if (length > 3) {
        throw std::runtime_error("Bold, Italic restricted to only 3 levels.");
    }
    this->_tokens.push_back(Token(BOLD_ITALIC, length));
}

void Lexer::handleUnderscore(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    unsigned long long length = 0;
    while (this->_index<source.size() && source[this->_index]=='_') {
        length++;
        this->_index++;
    }
    if (length == 0) {
        return;
    }
    if (length > 3) {
        throw std::runtime_error("Bold, Italic restricted to only 3 levels.");
    }
    this->_tokens.push_back(Token(BOLD_ITALIC, length));
}

void Lexer::handleTilda(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    if (source[this->_index] == '~') {
        this->_index++;
        this->_tokens.push_back(Token(STRIKETHROUGH));
    }
}

void Lexer::handleBacktick(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    unsigned short length = 0;
    while (this->_index<source.size() && source[this->_index]=='`') {
        length++;
        this->_index++;
    }
    if (length == 0) {
        return;
    }
    if (length==2 || length>3) {
        throw std::runtime_error("Code has only levels 1, 3.");
    }
    this->_tokens.push_back(Token(CODE, length));
}

void Lexer::handleGreater(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    if (source[this->_index] == '>') {
        this->_index++;
        this->_tokens.push_back(Token(QUOTE));
    }
}

void Lexer::handleNewline(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    if (source[this->_index] == '\n') {
        this->_index++;
        this->_tokens.push_back(Token(NEWLINE));
    }
}

void Lexer::handleText(const std::string& source) {
    if (this->_index >= source.size()) {
        return;
    }
    unsigned long long int length = 0, initIndex = this->_index;
    while (this->_index<source.size() && !this->specialChar(source[this->_index])) {
        length++;
        this->_index++;
    }
    if (length == 0) {
        return;
    }
    this->_tokens.push_back(Token(TEXT, source.substr(initIndex, length)));
}

ASTNode::ASTNode(const Token& token): token(token) {}

void ASTNode::addChild(ASTNode* child) {
    if (child == nullptr) {
        return;
    }
    this->children.push_back(child);
}

ASTNode* ASTNode::lastInsertedChild() {
    if (this->children.size() < 1) return nullptr;
    return this->children.back();
}

AST::AST() {
    this->_root = new ASTNode(Token(ROOT));
}

AST::~AST() {
    delete(this->_root);
    delete(this->_iterator);
}

void AST::load(const std::vector<Token>& tokens) {
    this->_iterator = this->_root;
    this->_iteratorHistory.push(this->_root);
    for (const Token& token: tokens) {
        std::cout << "Log: Token: "; token.log();
        std::cout << "\nLog: Last Token: "; this->_iterator->token.log(); std::cout << "\n";
        if (
            this->_iteratorHistory.top()->token == token ||
            this->_iteratorHistory.top()->token.type()==HEADING && token.type()==NEWLINE
        ) {
            this->_iteratorHistory.pop();
            this->_iterator = this->_iteratorHistory.top();
        }
        else {
            this->_iterator->addChild(new ASTNode(token));
            if (token.type() != TEXT) {
                this->_iteratorHistory.push(this->_iterator->lastInsertedChild());
                this->_iterator = this->_iterator->lastInsertedChild();
            }
        }
    }
}