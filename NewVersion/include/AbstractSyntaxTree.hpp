#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "AbstractSyntaxTreeNode.hpp"

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