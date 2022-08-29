#include "AbstractSyntaxTree.hpp"

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