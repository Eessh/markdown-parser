#include "Lexer.hpp"

Lexer::Lexer() {
	this->_tokens = std::vector<Token>();
	this->_index = 0;
}

const std::vector<Token>& Lexer::parseStrToTokens(const std::string& source) {
	this->_tokens.clear();
	this->_index = 0;
	this->commonFunc(source);
	return this->_tokens;
}

const std::vector<Token>& Lexer::parseDocToTokens(const MarkdownDoc& doc) {
	this->_tokens.clear();
	this->_index = 0;
	for (const std::string& line: doc.docData) {
		std::cout << "Log: Line: " << line << "\n";
		this->commonFunc(line);
		this->_tokens.push_back(Token(NEWLINE));
		this->_index = 0;
	}
	this->_tokens.pop_back();
	return this->_tokens;
}

void Lexer::commonFunc(const std::string& source) {
	while (this->_index < source.size()) {
		this->handleHash(source);
		this->handleAsterisk(source);
		this->handleUnderscore(source);
		this->handleTilda(source);
		this->handleBacktick(source);
		this->handleGreater(source);
		this->handleNewline(source);
		this->handleText(source);
	}
}

bool Lexer::specialChar(const char& c) {
	if (
		c == '#' ||
		c == '*' ||
		c == '_' ||
		c == '~' ||
		c == '`' ||
		c == '>' ||
		c == '\n'
	) {
		return true;
	}
	return false;
}

void Lexer::handleHash(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	unsigned long long length = 0;
	while (this->_index<source.size() && source[this->_index]=='#') {
		length++;
		this->_index++;
	}
	if (length == 0) {
		return;
	}
	if (length > 6) {
		throw std::runtime_error("Headings restricted to only 6 levels.");
	}
	this->_tokens.push_back(Token(HEADING, length));
}

void Lexer::handleAsterisk(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	unsigned long long length = 0;
	while (this->_index<source.size() && source[this->_index]=='*') {
		length++;
		this->_index++;
	}
	if (length == 0) {
		return;
	}
	if (length > 3) {
		throw std::runtime_error("Bold, Italic restricted to only 3 levels.");
	}
	this->_tokens.push_back(Token(BOLD_ITALIC, length));
}

void Lexer::handleUnderscore(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	unsigned long long length = 0;
	while (this->_index<source.size() && source[this->_index]=='_') {
		length++;
		this->_index++;
	}
	if (length == 0) {
		return;
	}
	if (length > 3) {
		throw std::runtime_error("Bold, Italic restricted to only 3 levels.");
	}
	this->_tokens.push_back(Token(BOLD_ITALIC, length));
}

void Lexer::handleTilda(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	if (source[this->_index] == '~') {
		this->_index++;
		this->_tokens.push_back(Token(STRIKETHROUGH));
	}
}

void Lexer::handleBacktick(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	unsigned short length = 0;
	while (this->_index<source.size() && source[this->_index]=='`') {
		length++;
		this->_index++;
	}
	if (length == 0) {
		return;
	}
	if (length==2 || length>3) {
		throw std::runtime_error("Code has only levels 1, 3.");
	}
	this->_tokens.push_back(Token(CODE, length));
}

void Lexer::handleGreater(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	if (source[this->_index] == '>') {
		this->_index++;
		this->_tokens.push_back(Token(QUOTE));
	}
}

void Lexer::handleNewline(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	if (source[this->_index] == '\n') {
		this->_index++;
		this->_tokens.push_back(Token(NEWLINE));
	}
}

void Lexer::handleText(const std::string& source) {
	if (this->_index >= source.size()) {
		return;
	}
	unsigned long long int length = 0, initIndex = this->_index;
	while (this->_index<source.size() && !this->specialChar(source[this->_index])) {
		length++;
		this->_index++;
	}
	if (length == 0) {
		return;
	}
	this->_tokens.push_back(Token(TEXT, source.substr(initIndex, length)));
}