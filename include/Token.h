#pragma once

#include <iostream>

using namespace std;

typedef enum {
	ROOT,
	HEADING1,
	HEADING2,
	HEADING3,
	HEADING4,
	HEADING5,
	HEADING6,
	BOLD,
	ITALIC,
	BOLDnITALIC,
	STRIKETHROUGH,
	INLINE_CODE,
	MULTILINE_CODE,
	TEXT
} TokenType;

class Token {
public:
	TokenType _type;
	string _value;

	Token(TokenType type);
	Token(TokenType type, const string &value);

	bool isHeading();
	bool isHeading1();
	bool isHeading2();
	bool isHeading3();
	bool isHeading4();
	bool isHeading5();
	bool isHeading6();
	bool isBold();
	bool isItalic();
	bool isBoldAndItalic();
	bool isStrikethrough();
	bool isCode();
	bool isInlineCode();
	bool isMultilineCode();
	bool isText();

	string toString();
};