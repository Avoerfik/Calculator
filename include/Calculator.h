#pragma once

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <complex>

class Calculator
{
public:
	std::stack<std::string> bracketAnalyze(const std::string& expression);
	std::string calculateExpression(std::stack<std::string>& expressionStack);

private:
	const std::string operators = "+-*/^";
	const std::string numbers = "0123456789";
	const std::string validSymbols = "+-*/^()0123456789.";

	struct Order
	{
		std::size_t index, priority;
	};

	struct Correspond
	{
		std::string bracketName, bracketValue;
	};

	void analyzeFirstSymbol(const char symbol, const std::size_t index, std::stack<std::size_t>& bracketStack,
		std::stack<bool>& bracketStackAnalyze, bool& start);
	void analyzeLastSymbol(const std::string& expression, const std::size_t index, std::stack<std::size_t>& bracketStack,
		std::stack<bool>& bracketStackAnalyze, std::stack<std::string>& expressionStackReverse, bool& end);
	void analyzeOperatorNearBrackets(const std::size_t index, const std::string& expression);
	void addNumberAndSign(const std::size_t& index, const std::string& bracket, std::vector<std::string>& bracketParsed,
		int& dotCount, std::string& number, bool& check);
	void checkNumber(const bool check, const std::string& bracket, const std::size_t& index, std::string& number, int& dotCount);
	void parseBrackets(const std::string& bracket, std::vector<std::string>& bracketParsed, int& dotCount);
	void setPriority(std::vector<std::string>& bracketParsed, std::vector<Order>& bracketPriority);
	void insertNewElem(std::vector<Order>& bracketPriority, std::vector<std::string>& bracketParsed);
	void handleNonEvaluableExpression(int& dotCount, const std::string& bracket, std::string& result);
	void handleEvaluableExpression(const std::string& bracket, int& dotCount, std::string& result);
	std::string calculateBracket(const std::string& bracket);
	void oneMainBracket(const std::string& expressionName, std::string& expressionValue, Correspond& cell,
		std::vector<Correspond>& table, std::stack<std::string>& expressionStack);
	void zeroMainBracket(const std::string& expressionName, std::string& expressionValue, Correspond& cell,
		std::vector<Correspond>& table, std::stack<std::string>& expressionStack);
	void replaceExpressionName(std::string& expressionName, std::string& expressionValue, Correspond& cell, std::vector<Correspond>& table,
		std::stack<std::string>& expressionStack, std::stack<std::string>& tempStackReverse);
	void iteration(std::string& expressionName, std::string& expressionValue, std::stack<std::string>& expressionStack,
		std::stack<std::string>& tempStackReverse, Correspond& cell, std::vector<Correspond>& table);
	
	inline bool isInt(const std::string& str);
	inline bool isOneBracket(const std::string& expression);
	inline bool isZeroBracket(const std::string& expression);
	inline bool isNotRepeatInVector(const std::vector<Correspond>& vect, const Correspond elem);
	inline std::string killSigns(std::string& number);
	inline std::string calculateOneExpression(const std::string& operand1, const std::string& operand2, const char operator12);
	inline std::stack<std::string> reverseStack(std::stack<std::string>& source,
												std::stack<std::string>& destination, const std::string& expression);
};

bool Calculator::isInt(const std::string& str)
{
	for (const char i : str) if (i == '.') return false;

	return true;
}

bool Calculator::isOneBracket(const std::string& expression)
{
	int brecketCount = 0;
	for (const char i : expression)
	{
		if (i == '(') ++brecketCount;
		if (brecketCount > 1) return false;
	}
	if (brecketCount == 0) return false;

	return true;
}

bool Calculator::isZeroBracket(const std::string& expression)
{
	int brecketCount = 0;
	for (const char i : expression)
	{
		if (i == '(') ++brecketCount;
		if (brecketCount > 0) return false;
	}

	return true;
}

bool Calculator::isNotRepeatInVector(const std::vector<Correspond>& vect, const Correspond elem)
{
	for (const auto& i : vect) if ((i.bracketName == elem.bracketName) && (i.bracketValue == elem.bracketValue)) return false;

	return true;
}

std::string Calculator::killSigns(std::string& number)
{
	size_t pos = number.find('+');
	while (pos != std::string::npos)
	{
		number.erase(pos, 1);
		pos = number.find('+');
	}

	int minus_count = 0;
	pos = 0;
	for (const char c : number)
	{
		if (c == '-') minus_count++;
		else break;
	}
	number.erase(0, minus_count);
	if (minus_count % 2 == 1) number = "-" + number;

	if (number == "-0") number = "0";

	return number;
}

std::string Calculator::calculateOneExpression(const std::string& operand1, const std::string& operand2, const char operator12)
{
	if (operator12 == '/')
	{
		if (operand2 == "0" || operand2 == "0.0" || stold(operand2) == 0.0)
		{
			throw std::runtime_error("Divide by zero!");
		}
	}
	if (operator12 == '^')
	{
		if ((operand1 == "0" || operand1 == "0.0" || stold(operand1) == 0.0) && (stold(operand2) < 0.0))
		{
			throw std::runtime_error("Divide by zero!");
		}
		if ((stold(operand1) < 0.0) && (!isInt(operand2)) /* && (int64_t(1 / stold(operand2)) % 2 == 0)*/)
		{
			std::complex<long double> cop1(stold(operand1), 0.0), cop2(stold(operand2), 0.0);
			std::complex powered = pow(cop1, cop2);
			long double real_part = powered.real();
			long double image_part = powered.imag();
			return std::to_string(real_part) + " + " + std::to_string(image_part) + "i";
		}
	}

	std::string result;
	if (isInt(operand1) && isInt(operand2))
	{
		long long op1 = stoll(operand1);
		long long op2 = stoll(operand2);

		switch (operator12)
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
			else result = std::to_string(stold(operand1) / stold(operand2));
			break;
		case '^':
			if (stold(operand2) >= 0.0) result = std::to_string(int64_t(powl(stold(operand1), stold(operand2))));
			else result = std::to_string(powl(stold(operand1), stold(operand2)));
			break;
		}
	}
	else
	{
		long double op1 = stold(operand1);
		long double op2 = stold(operand2);

		switch (operator12)
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
		case '^':
			result = std::to_string(powl(op1, op2));
			break;
		}
	}

	return result;
}

std::stack<std::string> Calculator::reverseStack(std::stack<std::string>& source, std::stack<std::string>& destination, const std::string& expression)
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