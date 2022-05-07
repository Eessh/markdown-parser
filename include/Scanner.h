#pragma once

#include <iostream>
#include <vector>
#include "Tokenizer.h"

using namespace std;

class Scanner {
public:
	Scanner();

	vector <Token*> scan(const string &markdownStr);

private:
	string _str;
	int _iteratorPos;
	vector <Token*> _tokens;

	bool _isSpecialChar();

	void _handleHashtag();
	void _handleAsterisk();
	void _handleUnderscore();
	void _handleTilda();
	void _handleBacktick();
	void _handleQuote();
	void _handleText();
};