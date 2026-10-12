#include "../App/include/lexer.h"

lexer::lexer()
{

}

lexer::~lexer()
{

}

std::vector<Token> lexer::setVectorTokens(std::string lexeme)
{
	const std::string numbers = "0123456789.";
	const std::string operators = "+-*/^";
	const std::string brackets = "()";
	std::string prevToken = "";
	for (std::size_t i = 0; i < lexeme.size(); i++)
	{
		if (numbers.find(lexeme[i]) != std::string::npos)
		{
			prevToken.push_back(lexeme[i]);
		}
		else if (operators.find(lexeme[i]) != std::string::npos)
		{

		}
		else if (brackets.find(lexeme[i]) != std::string::npos)
		{

		}
		else
		{

		}
	}
}