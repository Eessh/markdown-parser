#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Token.h"
#include "AbstractSyntaxTree.h"

using namespace std;

class Renderer {
public:
	Renderer();

	string renderTokens(const vector <Token*> &tokens);
	string renderHTML(const vector <Token*> &tokens);
	string renderAbstractSyntaxTree(AbstractSyntaxTree *AST);

private:
	string _currentTextStr;

	string recursiveASTRenderer(const AbstractSyntaxTreeNode* node);

	void surroundHeadingTags(string &_currentTextStr, int tagNumber);
	void surroundBoldTags(string &_currentTextStr);
	void surroundItalicTags(string &_currentTextStr);
	void surroundBoldAndItalicTags(string &_currentTextStr);
	void surroundStrikethroughTags(string &_currentTextStr);
	void surroundCodeTags(string &_currentTextStr);
	void surroundQuoteTags(string &_currentTextStr);
};