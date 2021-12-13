#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Token.h"

using namespace std;

class AbstractSyntaxTreeNode {
public:
	Token* _token;
	vector <AbstractSyntaxTreeNode*> _children;

	AbstractSyntaxTreeNode(Token* token);
};

class AbstractSyntaxTree {
private:
	AbstractSyntaxTreeNode* _root;
	AbstractSyntaxTreeNode* _iterator;
	stack <AbstractSyntaxTreeNode*> _iteratorHistory;

public:
	AbstractSyntaxTree();
	AbstractSyntaxTree(const vector <Token*> &tokens);

	AbstractSyntaxTreeNode* root();

  AbstractSyntaxTreeNode* lastVisitedNode();
  void pushNode(AbstractSyntaxTreeNode* node);
  void popHistory();
};
