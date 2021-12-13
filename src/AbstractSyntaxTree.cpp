#include "../include/AbstractSyntaxTree.h"

AbstractSyntaxTreeNode::AbstractSyntaxTreeNode(Token *token): _token(token) {}

AbstractSyntaxTree::AbstractSyntaxTree(): _root(nullptr), _iterator(nullptr) {}

AbstractSyntaxTree::AbstractSyntaxTree(const vector <Token*> &tokens) {
	_root = new AbstractSyntaxTreeNode(new Token(ROOT));
	_iterator = _root;
	_iteratorHistory.push(_root);
	for (Token* token: tokens) {
		if (token->_type == _iteratorHistory.top()->_token->_type) {
			_iteratorHistory.pop();
			_iterator = _iteratorHistory.top();
		}
		else {
			_iterator->_children.push_back(new AbstractSyntaxTreeNode(token));
			if (!token->isText()) {
				_iteratorHistory.push(_iterator->_children.back());
				_iterator = _iterator->_children.back();
			}
		}
	}
}

AbstractSyntaxTreeNode* AbstractSyntaxTree::root() {
	return _root;
}

AbstractSyntaxTreeNode* AbstractSyntaxTree::lastVisitedNode() {
  return _iteratorHistory.top();
}

void AbstractSyntaxTree::pushNode(AbstractSyntaxTreeNode* node) {
  _iteratorHistory.push(node);
  return;
}

void AbstractSyntaxTree::popHistory() {
  _iteratorHistory.pop();
  return;
}
