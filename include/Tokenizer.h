#pragma once

#include <iostream>
#include "Token.h"

using namespace std;

class Tokenizer {
public:
	Tokenizer();

	Token* tokenize(const string &tokenStr, const string &value);
};