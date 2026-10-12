#pragma once

#ifndef LEXER_H
#define LEXER_H

#include <vector>

#include "Tokens.h"

class lexer
{
public:
	lexer();
	~lexer();

	std::vector<Token> getVectorTokens() { return vectorTokens; };
	std::vector<Token> setVectorTokens(const std::string lexeme);

private:
	std::vector<Token> vectorTokens;

	bool checkNumber(std::string number);
};

#endif // !LEXER_H