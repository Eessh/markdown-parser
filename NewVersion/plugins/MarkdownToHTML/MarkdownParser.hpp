#ifndef MARKDOWN_PARSER
#define MARKDOWN_PARSER

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <stdexcept>




/*
 * Declarations
 */
class MarkdownDoc {
  public:
  std::vector<std::string> docData;
  
  MarkdownDoc();

  void load(const std::string& filepath);
  void log();
};

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
inline std::string tokenTypeToStr(const TokenType& type) {
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

inline Token::Token(const TokenType& type) {
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

inline Token::Token(const TokenType& type, const unsigned short& level) {
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

inline Token::Token(const TokenType& type, const std::string& value) {
  if (type != TEXT) {
    throw std::runtime_error("Token only of type: TEXT can be initalized with type and value.");
  }
  this->_type = type;
  this->_value = value;
}

inline TokenType Token::type() const {
  return this->_type;
}

inline unsigned short Token::level() const {
  if (
    this->_type != HEADING &&
    this->_type != BOLD_ITALIC &&
    this->_type != CODE
  ) {
    throw std::runtime_error("Level can only be accessed in tokens of type: HEADING, BOLD_ITALIC, CODE.");
  }
  return this->_level;
}

inline std::string Token::value() const {
  if (this->_type != TEXT) {
    throw std::runtime_error("Value can only be accessed in token of type: TEXT.");
  }
  return this->_value;
}

inline bool Token::operator == (const Token& token) {
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

inline void Token::log() const {
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

inline Lexer::Lexer() {
  this->_tokens = std::vector<Token>();
  this->_index = 0;
}

inline const std::vector<Token>& Lexer::parseStrToTokens(const std::string& source) {
  this->_tokens.clear();
  this->_index = 0;
  this->commonFunc(source);
  return this->_tokens;
}

inline const std::vector<Token>& Lexer::parseDocToTokens(const MarkdownDoc& doc) {
  this->_tokens.clear();
  this->_index = 0;
  for (const std::string& line: doc.docData) {
    this->commonFunc(line);
    this->_tokens.push_back(Token(NEWLINE));
    this->_index = 0;
  }
  this->_tokens.pop_back();
  return this->_tokens;
}

inline void Lexer::commonFunc(const std::string& source) {
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
}

inline bool Lexer::specialChar(const char& c) {
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

inline void Lexer::handleHash(const std::string& source) {
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

inline void Lexer::handleAsterisk(const std::string& source) {
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

inline void Lexer::handleUnderscore(const std::string& source) {
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

inline void Lexer::handleTilda(const std::string& source) {
  if (this->_index >= source.size()) {
    return;
  }
  if (source[this->_index] == '~') {
    this->_index++;
    this->_tokens.push_back(Token(STRIKETHROUGH));
  }
}

inline void Lexer::handleBacktick(const std::string& source) {
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

inline void Lexer::handleGreater(const std::string& source) {
  if (this->_index >= source.size()) {
    return;
  }
  if (source[this->_index] == '>') {
    this->_index++;
    this->_tokens.push_back(Token(QUOTE));
  }
}

inline void Lexer::handleNewline(const std::string& source) {
  if (this->_index >= source.size()) {
    return;
  }
  if (source[this->_index] == '\n') {
    this->_index++;
    this->_tokens.push_back(Token(NEWLINE));
  }
}

inline void Lexer::handleText(const std::string& source) {
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

inline ASTNode::ASTNode(const Token& token): token(token) {}

inline void ASTNode::addChild(ASTNode* child) {
  if (child == nullptr) {
    return;
  }
  this->children.push_back(child);
}

inline ASTNode* ASTNode::lastInsertedChild() {
  if (this->children.size() < 1) return nullptr;
  return this->children.back();
}

inline AST::AST() {
  this->_root = new ASTNode(Token(ROOT));
}

inline AST::~AST() {
  delete(this->_root);
  delete(this->_iterator);
}

inline void AST::load(const std::vector<Token>& tokens) {
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

inline MarkdownDoc::MarkdownDoc() {};

inline void MarkdownDoc::load(const std::string& filepath) {
  std::ifstream file;
  file.open(filepath, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  std::string s;
  while (file.good()) {
    std::getline(file, s);
    this->docData.push_back(s);
  }
}

inline void MarkdownDoc::log() {
  std::cout << "MarkdownDoc:\n";
  for (const std::string& s: this->docData) {
    std::cout << s << "\n";
  }
}

#endif  // MARKDOWN_PARSER