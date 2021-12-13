#include "../include/Tokenizer.h"

Tokenizer::Tokenizer() {}

Token* Tokenizer::tokenize(const string &tokenStr, const string &value) {
	if (tokenStr == "#") return new Token(HEADING1);
	if (tokenStr == "##") return new Token(HEADING2);
	if (tokenStr == "###") return new Token(HEADING3);
	if (tokenStr == "####") return new Token(HEADING4);
	if (tokenStr == "#####") return new Token(HEADING5);
	if (tokenStr == "######") return new Token(HEADING6);
	if (tokenStr=="*" || tokenStr=="_") return new Token(ITALIC);
	if (tokenStr=="**" || tokenStr=="__") return new Token(BOLD);
	if (tokenStr == "~~") return new Token(STRIKETHROUGH);
	if (tokenStr == "`") return new Token(INLINE_CODE);
	if (tokenStr == "```") return new Token(MULTILINE_CODE);
	return new Token(TEXT);
}