#include "../include/Scanner.h"

Scanner::Scanner(): _str(""), _iteratorPos(0) {}

vector <Token*> Scanner::scan(const string &markdownStr) {
	_str = markdownStr;
	_tokens.clear();
	_iteratorPos = 0;
	while (_iteratorPos < _str.size()) {
		if (!_isSpecialChar()) _handleText();
		if (_str[_iteratorPos] == '#') _handleHashtag();
		if (_str[_iteratorPos] == '*') _handleAsterisk();
		if (_str[_iteratorPos] == '_') _handleUnderscore();
		if (_str[_iteratorPos] == '~') _handleTilda();
		if (_str[_iteratorPos] == '`') _handleBacktick();
		if (_str[_iteratorPos] == '>') _handleQuote();
	}
	return _tokens;
}

bool Scanner::_isSpecialChar() {
	if (_str.empty()) return false;
	if (_str[_iteratorPos] == '#' ||
			_str[_iteratorPos] == '*' ||
			_str[_iteratorPos] == '_' ||
			_str[_iteratorPos] == '~' ||
			_str[_iteratorPos] == '`' ||
			_str[_iteratorPos] == '>') return true;
	return false;
}

void Scanner::_handleHashtag() {
	int length = 0;
	while (_iteratorPos < _str.size() && _str[_iteratorPos] == '#') {
		length += 1;
		_iteratorPos += 1;
	}
	if (length == 1) _tokens.push_back(new Token(HEADING1));
	else if (length == 2) _tokens.push_back(new Token(HEADING2));
	else if (length == 3) _tokens.push_back(new Token(HEADING3));
	else if (length == 4) _tokens.push_back(new Token(HEADING4));
	else if (length == 5) _tokens.push_back(new Token(HEADING5));
	else _tokens.push_back(new Token(HEADING6));
	return;
}

void Scanner::_handleAsterisk() {
	if (_str[_iteratorPos+2] == '*') {
		_tokens.push_back(new Token(BOLDnITALIC));
		_iteratorPos += 2;
	}
	else if (_str[_iteratorPos+1] == '*') {
		_tokens.push_back(new Token(BOLD));
		_iteratorPos += 1;
	}
	else _tokens.push_back(new Token(ITALIC));
	_iteratorPos += 1;
	return;
}

void Scanner::_handleUnderscore() {
	_iteratorPos += 1;
	if (_str[_iteratorPos] == '_') {
		_tokens.push_back(new Token(BOLD));
		_iteratorPos += 1;
	}
	else _tokens.push_back(new Token(ITALIC));
	return;
}

void Scanner::_handleTilda() {
	_iteratorPos += 1;
	if (_str[_iteratorPos] == '~') _tokens.push_back(new Token(STRIKETHROUGH));
	return;
}

void Scanner::_handleBacktick() {
	if (_str[_iteratorPos+2] == '`') {
		_tokens.push_back(new Token(MULTILINE_CODE));
		_iteratorPos += 3;
	}
	else {
		_tokens.push_back(new Token(INLINE_CODE));
		_iteratorPos += 1;
	}
	return;
}

void Scanner::_handleQuote() {
	_tokens.push_back(new Token(QUOTE));
	_iteratorPos += 1;
	return;
}

void Scanner::_handleText() {
	string text;
	while (_iteratorPos < _str.size() && !_isSpecialChar()) {
		text.push_back(_str[_iteratorPos]);
		_iteratorPos += 1;
	}
	_tokens.push_back(new Token(TEXT, text));
	return;
}
