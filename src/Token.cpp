#include "../include/Token.h"

Token::Token(TokenType type): _type(type) {}
Token::Token(TokenType type, const string &value): _type(type), _value(value) {}

bool Token::isHeading() {
	if (_type == HEADING1 ||
			_type == HEADING2 ||
			_type == HEADING3 ||
			_type == HEADING4 ||
			_type == HEADING5 ||
			_type == HEADING6) return true;
	return false;
}

bool Token::isHeading1() {
	if (_type == HEADING1) return true;
	return false;
}
bool Token::isHeading2() {
	if (_type == HEADING2) return true;
	return false;
}
bool Token::isHeading3() {
	if (_type == HEADING3) return true;
	return false;
}
bool Token::isHeading4() {
	if (_type == HEADING4) return true;
	return false;
}
bool Token::isHeading5() {
	if (_type == HEADING5) return true;
	return false;
}
bool Token::isHeading6() {
	if (_type == HEADING6) return true;
	return false;
}

bool Token::isBold() {
	if (_type == BOLD) return true;
	return false;
}

bool Token::isItalic() {
	if (_type == ITALIC) return true;
	return false;
}

bool Token::isStrikethrough() {
	if (_type == STRIKETHROUGH) return true;
	return false;
}

bool Token::isCode() {
	if (_type == INLINE_CODE || _type == MULTILINE_CODE) return true;
	return false;
}

bool Token::isInlineCode() {
	if (_type == INLINE_CODE) return true;
	return false;
}
bool Token::isMultilineCode() {
	if (_type == MULTILINE_CODE) return true;
	return false;
}

bool Token::isText() {
	if (_type == TEXT) return true;
	return false;
}

string Token::toString() {
	switch (_type) {
		case HEADING1:
			return "<HEADING1>";
		case HEADING2:
			return "<HEADING2>";
		case HEADING3:
			return "<HEADING3>";
		case HEADING4:
			return "<HEADING4>";
		case HEADING5:
			return "<HEADING5>";
		case HEADING6:
			return "<HEADING6>";
		case BOLD:
			return "<BOLD>";
		case ITALIC:
			return "<ITALIC>";
		case STRIKETHROUGH:
			return "<STRIKETHROUGH>";
		case INLINE_CODE:
			return "<INLINE_CODE>";
		case MULTILINE_CODE:
			return "<MULTILINE_CODE>";
		default:
			return "<TEXT value:'" + _value + "'>";
	}
}