#pragma once

#include <iostream>
#include <vector>
#include "Token.hpp"

class ASTNode {
    public:
    Token token;
    std::vector<ASTNode*> children;

    ASTNode(const Token& token);

    void addChild(ASTNode* child);
    ASTNode* lastInsertedChild();
};