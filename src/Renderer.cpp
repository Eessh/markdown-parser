#include "../include/Renderer.h"

Renderer::Renderer() {}

string Renderer::renderTokens(const vector <Token*> &tokens) {
	string str;
	for (Token* token: tokens) {
		str.append(token->toString());
	}
	return str;
}

string Renderer::renderHTML(const vector <Token*> &tokens) {
	_currentTextStr.clear();
	stack <Token*> tokenStack;
	for (Token* token: tokens) {
		if (tokenStack.empty()) {
			if (token->_type == TEXT) _currentTextStr = token->_value;
			else {
				tokenStack.push(token);
				_currentTextStr.clear();
			}
		}
		else if (tokenStack.top()->_type == token->_type) {
			// TODO
			// if (tokenStack.top()->)
		}
	}
  return "";
}

string Renderer::renderAbstractSyntaxTree(AbstractSyntaxTree* AST) {
	string str;
	if (AST == nullptr) return str;
	AbstractSyntaxTreeNode* root = AST->root();
	for (AbstractSyntaxTreeNode* child: root->_children) {
		str.append(recursiveASTRenderer(child));
	}
	return str;
}

string Renderer::recursiveASTRenderer(const AbstractSyntaxTreeNode* node) {
	if (node->_token->isText()) return node->_token->_value;
	string childrenStr;
	for (AbstractSyntaxTreeNode* child: node->_children) {
		childrenStr.append(recursiveASTRenderer(child));
	}
	if (node->_token->_type == HEADING1) surroundHeadingTags(childrenStr, 1);
	else if (node->_token->_type == HEADING2) surroundHeadingTags(childrenStr, 2);
	else if (node->_token->_type == HEADING3) surroundHeadingTags(childrenStr, 3);
	else if (node->_token->_type == HEADING4) surroundHeadingTags(childrenStr, 4);
	else if (node->_token->_type == HEADING5) surroundHeadingTags(childrenStr, 5);
	else if (node->_token->_type == HEADING6) surroundHeadingTags(childrenStr, 6);
	else if (node->_token->_type == BOLD) surroundBoldTags(childrenStr);
	else if (node->_token->_type == ITALIC) surroundItalicTags(childrenStr);
	else if (node->_token->_type == STRIKETHROUGH) surroundStrikethroughTags(childrenStr);
	else surroundCodeTags(childrenStr);
	return childrenStr;
}

void Renderer::surroundHeadingTags(string &_currentTextStr, int tagNumber) {
	const vector <pair <string, string>> tags = {
		{"<h1>", "</h1>"},
		{"<h2>", "</h2>"},
		{"<h3>", "</h3>"},
		{"<h4>", "</h4>"},
		{"<h5>", "</h5>"},
		{"<h6>", "</h6>"},
	};
	_currentTextStr = tags[tagNumber-1].first + _currentTextStr + tags[tagNumber-1].second;
	return;
}

void Renderer::surroundItalicTags(string &_currentTextStr) {
	_currentTextStr = "<em>" + _currentTextStr + "</em>";
	return;
}

void Renderer::surroundBoldTags(string &_currentTextStr) {
	_currentTextStr = "<b>" + _currentTextStr + "</b>";
	return;
}

void Renderer::surroundStrikethroughTags(string &_currentTextStr) {
	_currentTextStr = "<del>" + _currentTextStr + "</del>";
	return;
}

void Renderer::surroundCodeTags(string &_currentTextStr) {
	_currentTextStr = "<code>" + _currentTextStr + "</code>";
	return;
}