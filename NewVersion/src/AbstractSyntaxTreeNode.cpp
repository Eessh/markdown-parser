#include "AbstractSyntaxTreeNode.hpp"

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