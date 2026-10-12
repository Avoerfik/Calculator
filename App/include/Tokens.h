#pragma once

#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum class TokenType
{
	Number,
	UnaryPlus,
	UnaryMinus,
	BinaryPlus,
	BinaryMinus,
	Mult,
	Div,
	Exp,
	LeftBracket,
	RightBracket,
	End
};

struct Token
{
	TokenType type;
	std::string lexeme;
	long long number;
	unsigned long long position;
};

#endif // !TOKENS_H