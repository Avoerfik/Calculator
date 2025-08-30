#pragma once

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

const std::string operands = "+-*/";
const std::string numbers = "0123456789";
const std::string invalid_symbols = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ`~!@#$%^&_=[]{};':>?,<\"\\№|	";

struct Order
{
	std::size_t index, priority;
};

struct Correspond
{
	std::string bracketName, bracketValue;
};

void analyzeFirstSymbol(const char symbol, const size_t index, std::stack<std::size_t>& bracketStack,
	std::stack<bool>& bracketStackAnalyze, bool& start);
void analyzeLastSymbol(const std::string& expression, const size_t index, std::stack<std::size_t>& bracketStack,
	std::stack<bool>& bracketStackAnalyze, std::stack<std::string>& expressionStackReverse, bool& end);
void analyzeOperatorNearBrackets(const size_t index, const std::string& expression);
std::stack<std::string> reverseStack(std::stack<std::string>& source, std::stack<std::string>& destination, const std::string& expression);
std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateOneExpression(const std::string& operator1, const std::string& operator2, char operand);
std::string killSigns(std::string& number);
void addNumberAndSign(std::size_t& i, const std::string& bracket, std::vector<std::string>& bracketParsed,
	int& dotCount, std::string& number, bool& check);
void checkNumber(bool& check, const std::string& bracket, std::size_t& i, std::string& number, int& dotCount);
void parseBrackets(const std::string& bracket, std::vector<std::string>& bracketParsed, int& dotCount);
void setPriority(std::vector<std::string>& bracketParsed, std::vector<Order>& bracketPriority);
void insertNewElem(std::vector<Order>& bracketPriority, std::vector<std::string>& bracketParsed);
void handleNonEvaluableExpression(int& dotCount, const std::string& bracket, std::string& result);
void handleEvaluableExpression(const std::string& bracket, int& dotCount, std::string& result);
std::string calculateBracket(const std::string& bracket);
void oneMainBracket(std::string& expressionName, std::string& expressionValue, Correspond& cell,
	std::vector<Correspond>& table, std::stack<std::string>& expressionStack);
void zeroMainBracket(std::string& expressionName, std::string& expressionValue, Correspond& cell,
	std::vector<Correspond>& table, std::stack<std::string>& expressionStack);
void replaceExpressionName(std::string& expressionName, std::string& expressionValue, Correspond& cell, std::vector<Correspond>& table,
	std::stack<std::string>& expressionStack, std::stack<std::string>& tempStackReverse);
void iteration(std::string& expressionName, std::string& expressionValue, std::stack<std::string>& expressionStack,
	std::stack<std::string>& tempStackReverse, Correspond& cell, std::vector<Correspond>& table);
std::string calculateExpression(std::stack<std::string>& expressionStack);

inline bool isInt(const std::string& str)
{
	for (const auto& i : str) if (i == '.') return false;

	return true;
}

inline bool isOneBracket(const std::string& expression)
{
	int brecketCount = 0;
	for (const auto& i : expression)
	{
		if (i == '(') ++brecketCount;
		if (brecketCount > 1) return false;
	}
	if (brecketCount == 0) return false;
	return true;
}

inline bool isZeroBracket(const std::string& expression)
{
	int brecketCount = 0;
	for (const auto& i : expression)
	{
		if (i == '(') ++brecketCount;
		if (brecketCount > 0) return false;
	}
	return true;
}

inline bool isNotRepeatInVector(std::vector<Correspond>& vect, Correspond elem)
{
	for (const auto& i : vect) if ((i.bracketName == elem.bracketName) && (i.bracketValue == elem.bracketValue)) return false;

	return true;
}

inline std::string killSigns(std::string& number)
{
	size_t pos = number.find('+');
	while (pos != std::string::npos)
	{
		number.erase(pos, 1);
		pos = number.find('+');
	}

	int minus_count = 0;
	pos = 0;
	for (char c : number)
	{
		if (c == '-') minus_count++;
		else break;
	}
	number.erase(0, minus_count);
	if (minus_count % 2 == 1) number = "-" + number;

	if (number == "-0") number = "0";

	return number;
}

inline std::string calculateOneExpression(const std::string& operator1, const std::string& operator2, char operand)
{
	if (operand == '/')
	{
		if (operator2 == "0" || operator2 == "0.0" || stold(operator2) == 0.0)
		{
			throw std::runtime_error("Divide by zero!");
		}
	}

	std::string result;
	if (isInt(operator1) && isInt(operator2))
	{
		long long op1 = stoll(operator1);
		long long op2 = stoll(operator2);

		switch (operand)
		{
		case '+':
			result = std::to_string(op1 + op2);
			break;
		case '-':
			result = std::to_string(op1 - op2);
			break;
		case '*':
			result = std::to_string(op1 * op2);
			break;
		case '/':
			if (op1 % op2 == 0)	result = std::to_string(op1 / op2);
			else result = std::to_string(stold(operator1) / stold(operator2));
			break;
		}
	}
	else
	{
		long double op1 = stold(operator1);
		long double op2 = stold(operator2);

		switch (operand)
		{
		case '+':
			result = std::to_string(op1 + op2);
			break;
		case '-':
			result = std::to_string(op1 - op2);
			break;
		case '*':
			result = std::to_string(op1 * op2);
			break;
		case '/':
			result = std::to_string(op1 / op2);
			break;
		}
	}

	return result;
}

inline std::stack<std::string> reverseStack(std::stack<std::string>& source, std::stack<std::string>& destination, const std::string& expression)
{
	if (source.empty())
	{
		destination.push(expression);
	}
	else
	{
		while (!source.empty())
		{
			destination.push(source.top());
			source.pop();
		}
	}
	return destination;
}

#endif // !CALCULATOR_H