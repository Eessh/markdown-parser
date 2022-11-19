/**
 * @file MarkdownParser.hpp
 * @brief Library for parsing markdown syntax to AST
 * 
 * This contains all the required classes prototypes
 * and their implementations.
 * 
 * @author Eessh
 * @bug Still need to implement iterators: RenderingIterator, Iterator.
 */


#ifndef MARKDOWN_PARSER
#define MARKDOWN_PARSER


///////////////////////////////////////////////////////////////////////////////
// * Includes
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <stdexcept>


///////////////////////////////////////////////////////////////////////////////
// * MarkdownParser Namespace
///////////////////////////////////////////////////////////////////////////////
namespace MarkdownParser {


  /////////////////////////////////////////////////////////////////////////////
  // * MArkdownDoc
  /////////////////////////////////////////////////////////////////////////////
  class MarkdownDoc {
    public:
    std::vector<std::string> docData;
    
    MarkdownDoc();

    void load(const std::string& filepath);
    void log();
  };


  /////////////////////////////////////////////////////////////////////////////
  // * TokenType
  /////////////////////////////////////////////////////////////////////////////
  typedef enum class TokenType {
    ROOT,
    HEADING,
    BOLD_ITALIC,
    STRIKETHROUGH,
    CODE,
    QUOTE,
    LINK,
    IMAGE,
    TEXT,
    NEWLINE
  } TokenType;
  std::string tokenTypeToStr(const TokenType& type);


  /////////////////////////////////////////////////////////////////////////////
  // * Token
  /////////////////////////////////////////////////////////////////////////////
  class Token {
    public:
    Token(const TokenType& type);
    Token(const TokenType& type, const unsigned short& level);
    Token(const TokenType& type, const std::string& value);

    TokenType type() const;
    unsigned short level() const;
    std::string value() const;

    unsigned long long startIndex() const;
    unsigned long long endIndex() const;

    bool operator == (const Token& token);

    void log() const;

    private:
    TokenType _type;
    unsigned short _level;
    std::string _value;
    unsigned long long _startIndex;
    unsigned long long _endIndex;
  };


  /////////////////////////////////////////////////////////////////////////////
  // * Lexer
  /////////////////////////////////////////////////////////////////////////////
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
    void handleOpenSquaredBracket(const std::string& source);
    void handleExclamation(const std::string& source);
    void handleText(const std::string& source);
  };


  /////////////////////////////////////////////////////////////////////////////
  // * ASTNode (Abstract Syntax Tree Node)
  /////////////////////////////////////////////////////////////////////////////
  class ASTNode {
    public:
    Token token;
    std::vector<ASTNode*> children;

    ASTNode(const Token& token);
    ~ASTNode();

    void addChild(ASTNode* child);
    ASTNode* lastInsertedChild();
  };


  /////////////////////////////////////////////////////////////////////////////
  // * AST (Abstract Syntax Tree)
  /////////////////////////////////////////////////////////////////////////////
  class AST {
    public:
    AST();
    ~AST();

    const ASTNode* root() const;
    
    void load(const std::vector<Token>& tokens);

    // // Iterators
    // class Iterator {
    // public:
    //   Iterator() noexcept;

    // private:
    //   const ASTNode* iterator;
    //   std::stack<ASTNode*> iteratorHistory;
    // };


    // class RenderingIterator {
    // public:
    //   RenderingIterator() noexcept;

    // private:
    //   const ASTNode* iterator;
    //   std::stack<ASTNode*> iteratorHistory;
    // };

    // RenderingIterator nextNodeToRender();

    private:
    ASTNode* _root;
    ASTNode* _iterator;
    std::stack<ASTNode*> _iteratorHistory;
  };




  /////////////////////////////////////////////////////////////////////////////
  // * TokenType Implementations
  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Converts TokenType to string.
   * 
   * Example: TokenType::ROOT => "ROOT"
   * 
   * @param type token type(TokenType)
   * @return string form of type
   * @throws No exceptions
   */
  inline std::string tokenTypeToStr(const TokenType& type) {
    switch (type) {
      case TokenType::ROOT:
        return "ROOT";
      case TokenType::HEADING:
        return "HEADING";
      case TokenType::BOLD_ITALIC:
        return "BOLD_ITALIC";
      case TokenType::STRIKETHROUGH:
        return "STRIKETHROUGH";
      case TokenType::CODE:
        return "CODE";
      case TokenType::QUOTE:
        return "QUOTE";
      case TokenType::TEXT:
        return "TEXT";
      default:
        break;
    }
    return "NEWLINE";
  }


  /////////////////////////////////////////////////////////////////////////////
  // * Token Implementations
  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Token constructor.
   * 
   * Token(const TokenType& type) should be used for tokens of type: ROOT, STRIKETHROUGH, QUOTE, NEWLINE.
   * 
   * @param type token type(TokenType)
   * @throws No exceptions
   */
  inline Token::Token(const TokenType& type) {
    if (
      type != TokenType::ROOT &&
      type != TokenType::STRIKETHROUGH &&
      type != TokenType::QUOTE &&
      type != TokenType::NEWLINE
    ) {
      throw std::runtime_error("Tokens only of type: ROOT, STRIKETHROUGH, QUOTE, NEWLINE can be initialized without value or level.");
    }
    this->_type = type;
  }

  /**
   * @brief Token constructor.
   * 
   * Token(const TokenType& type, const unsigned short& level) should be used for tokens if type: HEADING, BOLD_ITALIC, CODE.
   * 
   * @param type token type(TokenType)
   * @throws No exceptions
   */
  inline Token::Token(const TokenType& type, const unsigned short& level) {
    if (
      type != TokenType::HEADING &&
      type != TokenType::BOLD_ITALIC &&
      type != TokenType::CODE
    ) {
      throw std::runtime_error("Tokens only of type: HEADING, BOLD_ITALIC, CODE can be initialized with type and level.");
    }
    this->_type = type;
    this->_level = level;
  }

  /**
   * @brief Token constructor.
   * 
   * Token(const TokenType& type, const std::string& value) should be used for tokens of type: TEXT.
   * 
   * @param type token type(TokenType)
   * @throws No exceptions
   */
  inline Token::Token(const TokenType& type, const std::string& value) {
    if (type != TokenType::TEXT) {
      throw std::runtime_error("Token only of type: TEXT can be initalized with type and value.");
    }
    this->_type = type;
    this->_value = value;
  }

  /**
   * @brief Returns type of token.
   * 
   * @return type (TokenType)
   * @throws No exceptions
   */
  inline TokenType Token::type() const {
    return this->_type;
  }

  /**
   * @brief Returns level of token.
   * 
   * This method is only applicable to tokens of type: HEADING, BOLD_ITALIC, CODE.
   * 
   * @return level (unsigned short)
   * @throws Throws std::runtime_error, when accessing level of tokens of type: STRIKETHROUGH, QUOTE, TEXT, NEWLINE.
   */
  inline unsigned short Token::level() const {
    if (
      this->_type != TokenType::HEADING &&
      this->_type != TokenType::BOLD_ITALIC &&
      this->_type != TokenType::CODE
    ) {
      throw std::runtime_error("Level can only be accessed in tokens of type: HEADING, BOLD_ITALIC, CODE.");
    }
    return this->_level;
  }

  /**
   * @brief Returns value of token.
   * 
   * This method is only applicable to tokens of type: TEXT.
   * 
   * @return value (std::string)
   * @throws Throws std::runtime_error, when accessing value of tokens of type: ROOT, HEADING, BOLD_ITALIC, STRIKETHROUGH, CODE, QUOTE, NEWLINE.
   */
  inline std::string Token::value() const {
    if (this->_type != TokenType::TEXT) {
      throw std::runtime_error("Value can only be accessed in token of type: TEXT.");
    }
    return this->_value;
  }

  /**
   * @brief Checks if two Tokens are equal.
   * 
   * @param token A const reference to a Token, which is being compared with this.
   * @return true if two Tokens are equal.
   * @throws No exceptions
   */
  inline bool Token::operator == (const Token& token) {
    if (this->_type == token.type()) {
      switch (this->_type) {
        case TokenType::TEXT: {
          if (this->_value == token.value()) {
            #ifdef DEBUG
            std::cout << "Log: Returning true\n";
            #endif
            return true;
          }
          return false;
        }
        case TokenType::HEADING:
        case TokenType::BOLD_ITALIC:
        case TokenType::CODE: {
          if (this->_level == token.level()) {
            #ifdef DEBUG
            std::cout << "Log: Returning true\n";
            #endif
            return true;
          }
          return false;
        }
        default: {
          #ifdef DEBUG
          std::cout << "Log: Returning true\n";
          #endif
          return true;
        }
      }
    }
    return false;
  }

  /**
   * @brief Logs token to stdout.
   * 
   * Example:
   * 1) If token is of type ROOT, <ROOT> will be logged.
   * 2) If token is of type HEADING, with level 3; <HEADING 3> will be logged.
   * 
   * @return void
   * @throws No exceptions
   */
  inline void Token::log() const {
    switch (this->_type) {
      case TokenType::TEXT: {
        std::cout << "<TEXT '" << this->_value << ">";
        break;
      }
      case TokenType::HEADING:
      case TokenType::BOLD_ITALIC:
      case TokenType::CODE: {
        std::cout << "<" << tokenTypeToStr(this->_type) << " " << this->_level << ">";
        break;
      }
      default: {
        std::cout << "<" << tokenTypeToStr(this->_type) << ">";
        break;
      }
    }
  }


  /////////////////////////////////////////////////////////////////////////////
  // * Lexer Implementations
  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Default Constructor
   * 
   * @return void
   * @throws No exceptions
   */
  inline Lexer::Lexer() {
    this->_index = 0;
  }

  /**
   * @brief Parses markdown string to tokens.
   * 
   * @return Const reference to a vector of tokens.
   * @throws No exceptions
   */
  inline const std::vector<Token>& Lexer::parseStrToTokens(const std::string& source) {
    this->_tokens.clear();
    this->_index = 0;
    this->commonFunc(source);
    return this->_tokens;
  }

  /**
   * @brief Parses markdown document (MarkdownDoc) to tokens.
   * 
   * @return Const reference to a vector of tokens.
   * @throws No exceptions
   */
  inline const std::vector<Token>& Lexer::parseDocToTokens(const MarkdownDoc& doc) {
    this->_tokens.clear();
    this->_index = 0;
    for (const std::string& line: doc.docData) {
      this->commonFunc(line);
      this->_tokens.push_back(Token(TokenType::NEWLINE));
      this->_index = 0;
    }
    this->_tokens.pop_back();
    return this->_tokens;
  }

  /**
   * @brief This is the underlying function for MarkdownParser::Lexer::parseStrToTokens, MarkdownParser::Lexer::parseDocToTokens.
   * 
   * This function's job is to parse a markdown string to tokens, updates the iterator through source string, and parses into Tokens, at the same time.
   * 
   * @return Const reference to a vector of tokens.
   * @throws No exceptions
   */
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

  /**
   * @brief Checks whether an encountered character is a special character.
   * 
   * Special Charaters: '#', '*', '_', '~', '`', '>', '\n'
   * 
   * @return boolean
   * @throws No exceptions
   */
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
    this->_tokens.push_back(Token(TokenType::HEADING, length));
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
    this->_tokens.push_back(Token(TokenType::BOLD_ITALIC, length));
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
    this->_tokens.push_back(Token(TokenType::BOLD_ITALIC, length));
  }

  inline void Lexer::handleTilda(const std::string& source) {
    if (this->_index >= source.size()) {
      return;
    }
    if (source[this->_index] == '~') {
      this->_index++;
      this->_tokens.push_back(Token(TokenType::STRIKETHROUGH));
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
    this->_tokens.push_back(Token(TokenType::CODE, length));
  }

  inline void Lexer::handleGreater(const std::string& source) {
    if (this->_index >= source.size()) {
      return;
    }
    if (source[this->_index] == '>') {
      this->_index++;
      this->_tokens.push_back(Token(TokenType::QUOTE));
    }
  }

  inline void Lexer::handleNewline(const std::string& source) {
    if (this->_index >= source.size()) {
      return;
    }
    if (source[this->_index] == '\n') {
      this->_index++;
      this->_tokens.push_back(Token(TokenType::NEWLINE));
    }
  }

  inline void Lexer::handleOpenSquaredBracket(const std::string& source) {}
  
  inline void Lexer::handleExclamation(const std::string& source) {}

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
    this->_tokens.push_back(Token(TokenType::TEXT, source.substr(initIndex, length)));
  }


  /////////////////////////////////////////////////////////////////////////////
  // * ASTNode (Abstract Syntax Tree Node) Implementations
  /////////////////////////////////////////////////////////////////////////////
  inline ASTNode::ASTNode(const Token& token): token(token) {}

  inline ASTNode::~ASTNode() {
    for (ASTNode* child: this->children) delete(child);
  }

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


  /////////////////////////////////////////////////////////////////////////////
  // * AST Implementations
  /////////////////////////////////////////////////////////////////////////////
  inline AST::AST() {
    this->_root = new ASTNode(Token(TokenType::ROOT));
  }

  inline AST::~AST() {
    delete(this->_root);
    // delete(this->_iterator);
  }

  inline const ASTNode* AST::root() const {
    return this->_root;
  }

  inline void AST::load(const std::vector<Token>& tokens) {
    this->_iterator = this->_root;
    this->_iteratorHistory.push(this->_root);
    for (const Token& token: tokens) {
      #ifdef DEBUG
      std::cout << "Log: Token: "; token.log();
      std::cout << "\nLog: Last Token: "; this->_iterator->token.log(); std::cout << "\n";
      #endif
      if (
        this->_iteratorHistory.top()->token == token ||
        this->_iteratorHistory.top()->token.type()==TokenType::HEADING && token.type()==TokenType::NEWLINE
      ) {
        this->_iteratorHistory.pop();
        this->_iterator = this->_iteratorHistory.top();
      }
      else {
        this->_iterator->addChild(new ASTNode(token));
        if (token.type() != TokenType::TEXT) {
          this->_iteratorHistory.push(this->_iterator->lastInsertedChild());
          this->_iterator = this->_iterator->lastInsertedChild();
        }
      }
    }
  }

  // inline AST::RenderingIterator::RenderingIterator() noexcept {
  //   this->iterator = nullptr;
  // }

  // inline RenderingIterator AST::rootNodeToRender() {
  //   return RenderingIterator(this->_root);
  // }

  // inline RenderingIterator AST::nextNodeToRender() {}


  /////////////////////////////////////////////////////////////////////////////
  // * MarkdownDoc Implementations
  /////////////////////////////////////////////////////////////////////////////
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

}   // Namespace: MarkdownParser

#endif  // MARKDOWN_PARSER
