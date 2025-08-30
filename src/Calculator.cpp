#include "../include/Calculator.h"

void analyzeFirstSymbol(const char symbol, const size_t index, std::stack<std::size_t>& bracketStack,
						std::stack<bool>& bracketStackAnalyze, bool& start)
{
	if ((symbol == '(') && (index != 0))
	{
		bracketStack.push(index);
		bracketStackAnalyze.push(true);
	}
	if ((symbol == '(') && (index == 0))
	{
		bracketStack.push(index);
		bracketStack.push(index);
		bracketStackAnalyze.push(true);
		start = false;
	}
	if (start && (index == 0))
	{
		bracketStack.push(index);
	}
}

void analyzeLastSymbol(const std::string& expression, const size_t index, std::stack<std::size_t>& bracketStack,
					   std::stack<bool>& bracketStackAnalyze, std::stack<std::string>& expressionStackReverse, bool& end)
{
	if (expression[index] == ')')
	{
		if (!bracketStackAnalyze.empty()) bracketStackAnalyze.pop();
		else throw std::runtime_error("Invalid data format!");

		if (!bracketStack.empty())
		{
			size_t top_index = bracketStack.top();
			if (top_index <= index)
			{
				expressionStackReverse.push(expression.substr(top_index, index + 1 - top_index));
				bracketStack.pop();

				if (index == expression.size() - 1)
				{
					if (!bracketStack.empty())
					{
						top_index = bracketStack.top();
						if (top_index <= index)
						{
							expressionStackReverse.push(expression.substr(top_index, index + 1 - top_index));
							bracketStack.pop();
							end = false;
						}
					}
					else throw std::runtime_error("Invalid data format!");
				}
			}
			else throw std::runtime_error("Invalid bracket indices");
		}
		else throw std::runtime_error("Invalid data format!");
	}

	if (end && (index == expression.size() - 1))
	{
		if (!bracketStack.empty())
		{
			size_t top_index = bracketStack.top();
			if (top_index <= expression.size())
			{
				expressionStackReverse.push(expression.substr(top_index, expression.size() - top_index));
				bracketStack.pop();
			}
		}
		else throw std::runtime_error("Invalid data format!");
	}
}

void analyzeOperatorNearBrackets(const size_t index, const std::string& expression)
{
	if (index >= expression.size()) return;

	const char current = expression[index];

	if (index > 0)
	{
		char prev = expression[index - 1];
		if ((current == '(') &&
			(operands.find(prev) == std::string::npos) &&
			(prev != '('))
		{
			throw std::runtime_error("Invalid data format!");
		}
	}

	if (index < expression.size() - 1)
	{
		char next = expression[index + 1];
		if ((current == ')') &&
			(operands.find(next) == std::string::npos) &&
			(next != ')'))
		{
			throw std::runtime_error("Invalid data format!");
		}
	}
}

std::stack<std::string> bracketAnalyze(const std::string& expression)
{
	std::stack<std::size_t> bracketStack;
	std::stack<bool> bracketStackAnalyze;
	std::stack<std::string> expressionStackReverse, expressionStack;
	bool isNumber = false, start = true, end = true;

	if (expression.empty()) throw std::runtime_error("Empty expression");

	for (std::size_t i = 0; i < expression.size(); i++)
	{
		if (invalid_symbols.find(expression[i]) != std::string::npos) throw std::runtime_error("Invalid Symbols");
		if (numbers.find(expression[i]) != std::string::npos) isNumber = true;
		try
		{
			analyzeFirstSymbol(expression[i], i, bracketStack, bracketStackAnalyze, start);
			analyzeLastSymbol(expression, i, bracketStack, bracketStackAnalyze, expressionStackReverse, end);
			analyzeOperatorNearBrackets(i, expression);
		}
		catch (const std::exception& e)
		{
			throw;
		}		
	}

	if (!bracketStack.empty()) throw std::runtime_error("Invalid data format!");
	if (!isNumber) throw std::runtime_error("No Number");

	return reverseStack(expressionStackReverse, expressionStack, expression);
}

void addNumberAndSign(std::size_t& i, const std::string& bracket, std::vector<std::string>& bracketParsed,
					  int& dotCount, std::string& number, bool& check)
{
	if ((i != bracket.size() - 1) && (i != 0))
	{
		if ((operands.find(bracket[i]) != std::string::npos)
			&& ((numbers.find(bracket[i - 1]) != std::string::npos)
				|| (bracket[i - 1] == '.'))
			&& ((numbers.find(bracket[i + 1]) != std::string::npos)
				|| (bracket[i + 1] == '.')
				|| (bracket[i + 1] == '-')
				|| (bracket[i + 1] == '+')))
		{
			bracketParsed.push_back(killSigns(number));
			number = "";
			dotCount = 0;
			bracketParsed.push_back(std::string(1, bracket[i]));
			check = false;
		}
		else
		{
			check = true;
		}
	}
	else check = true;
}

void checkNumber(bool& check, const std::string& bracket, std::size_t& i, std::string& number, int& dotCount)
{
	if (check)
	{
		if ((numbers.find(bracket[i]) != std::string::npos)
			|| (bracket[i] == '.')
			|| (operands.find(bracket[i]) != std::string::npos))
		{
			number += bracket[i];
			if (bracket[i] == '.') ++dotCount;
			if (dotCount > 1)
			{
				throw std::runtime_error("Invalid data format!");
			}
		}
		if (i != 0)
		{
			if (((bracket[i] == '*') || (bracket[i] == '/')) && (numbers.find(bracket[i - 1]) == std::string::npos))
			{
				throw std::runtime_error("Invalid data format!");
			}
		}
	}
}

void parseBrackets(const std::string& bracket, std::vector<std::string>& bracketParsed, int& dotCount)
{
	try
	{
		std::string number;
		bool check = true;
		for (std::size_t i = 0; i < bracket.size(); i++)
		{
			addNumberAndSign(i, bracket, bracketParsed, dotCount, number, check);
			checkNumber(check, bracket, i, number, dotCount);
		}

		if (!number.empty()) bracketParsed.push_back(killSigns(number));
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void setPriority(std::vector<std::string>& bracketParsed, std::vector<Order>& bracketPriority)
{
	Order operation;
	std::size_t priority = 1;
	for (std::size_t i = 0; i < bracketParsed.size(); i++)
	{
		if ((bracketParsed[i][0] == '*') || (bracketParsed[i][0] == '/'))
		{
			operation = { i, priority++ };
			bracketPriority.push_back(operation);
		}
	}
	for (std::size_t i = 0; i < bracketParsed.size(); i++)
	{
		if ((bracketParsed[i] == "+") || (bracketParsed[i] == "-"))
		{
			operation = { i, priority++ };
			bracketPriority.push_back(operation);
		}
	}
}

void insertNewElem(std::vector<Order>& bracketPriority, std::vector<std::string>& bracketParsed)
{
	if (!bracketPriority.empty())
	{
		for (std::size_t i = 1; i <= bracketPriority.size(); i++)
		{
			for (std::size_t j = 0; j < bracketPriority.size(); j++)
			{
				if (i == bracketPriority[j].priority)
				{
					std::size_t opIndex = bracketPriority[j].index;
					if (opIndex == 0 || opIndex >= bracketParsed.size() - 1) continue;

					try
					{
						std::string newElem = calculateOneExpression(bracketParsed[bracketPriority[j].index - 1], bracketParsed[bracketPriority[j].index + 1], bracketParsed[bracketPriority[j].index][0]);
						bracketParsed.erase(bracketParsed.begin() + opIndex - 1, bracketParsed.begin() + opIndex + 2);

						if (opIndex - 1 < bracketParsed.size()) bracketParsed.insert(bracketParsed.begin() + opIndex - 1, newElem);
						else bracketParsed.push_back(newElem);

						for (std::size_t k = j + 1; k < bracketPriority.size(); k++) if (bracketPriority[k].index > opIndex) bracketPriority[k].index -= 2;
					}
					catch (const std::runtime_error& e)
					{
						throw;
					}

					break;
				}
			}
		}
	}
}

void handleNonEvaluableExpression(int& dotCount, const std::string& bracket, std::string& result)
{
	dotCount = 0;
	for (std::size_t i = 0; i < bracket.size(); i++)
	{
		if ((numbers.find(bracket[i]) != std::string::npos) || (bracket[i] == '.') || (i == 0) && (operands.find(bracket[i]) != std::string::npos))
		{
			if (bracket[i] == '.') ++dotCount;
			if (dotCount > 1)
			{
				throw std::runtime_error("Invalid data format!");
			}
		}
		else if ((operands.find(bracket[i]) != std::string::npos) && (i != 0))
		{
			dotCount = 0;
		}
	}

	if (bracket[0] != '+')	result = bracket;
	else result = bracket.substr(1, bracket.size());
}

void handleEvaluableExpression(const std::string& bracket, int& dotCount, std::string& result)
{
	std::vector<std::string> bracketParsed;
	try
	{
		std::vector<Order> bracketPriority;

		parseBrackets(bracket, bracketParsed, dotCount);
		setPriority(bracketParsed, bracketPriority);
		insertNewElem(bracketPriority, bracketParsed);
	}
	catch (const std::exception&)
	{
		throw;
	}

	if (bracketParsed[0][0] != '+')	result = bracketParsed[0];
	else result = bracketParsed[0].substr(1, bracketParsed[0].size());
}

std::string calculateBracket(const std::string& bracket)
{
	if ((bracket[0] == '*') || (bracket[0] == '/')) throw std::runtime_error("Invalid data format!");
	if ((operands.find(bracket[bracket.size() - 1]) != std::string::npos)) throw std::runtime_error("Invalid data format!");
	
	std::string result;
	bool isCalculatable = false;
	int dotCount = 0;
	try
	{
		for (int i = 0; i < 4; i++)	if (bracket.find(operands[i]) != std::string::npos) isCalculatable = true;
		if (isCalculatable)
		{
			handleEvaluableExpression(bracket, dotCount, result);
		}
		else
		{
			handleNonEvaluableExpression(dotCount, bracket, result);
		}
	}
	catch (const std::exception&)
	{
		throw;
	}

	return result;
}

void oneMainBracket(std::string& expressionName, std::string& expressionValue, Correspond& cell,
					std::vector<Correspond>& table, std::stack<std::string>& expressionStack)
{
	try
	{
		bool isNumber = false;
		for (const auto& i : expressionName) if (numbers.find(i) != std::string::npos) isNumber = true;
		if (isNumber)
		{

			expressionValue = calculateBracket(expressionName.substr(1, expressionName.size() - 2));
			cell.bracketName = expressionName;
			cell.bracketValue = expressionValue;
			if (isNotRepeatInVector(table, cell)) table.push_back(cell);
			expressionStack.pop();
		}
		else throw std::runtime_error("Invalid data format!");
	}
	catch (const std::runtime_error& e)
	{
		throw;
	}
}

void zeroMainBracket(std::string& expressionName, std::string& expressionValue, Correspond& cell,
					 std::vector<Correspond>& table, std::stack<std::string>& expressionStack)
{
	try
	{
		bool isNumber = false;
		for (const auto& i : expressionName) if (numbers.find(i) != std::string::npos) isNumber = true;
		if (isNumber)
		{
			expressionValue = calculateBracket(expressionName.substr(0, expressionName.size()));
			cell.bracketName = expressionName;
			cell.bracketValue = expressionValue;
			if (isNotRepeatInVector(table, cell)) table.push_back(cell);
			expressionStack.pop();
		}
		else throw std::runtime_error("Invalid data format!");
	}
	catch (const std::runtime_error& e)
	{
		throw;
	}
}

void replaceExpressionName(std::string& expressionName, std::string& expressionValue, Correspond& cell, std::vector<Correspond>& table,
						   std::stack<std::string>& expressionStack, std::stack<std::string>& tempStackReverse)
{
	std::size_t pos;
	for (const auto& i : table)
	{
		pos = expressionName.find(i.bracketName);
		if (pos != std::string::npos)
		{
			expressionName = expressionName.replace(pos, i.bracketName.size(), i.bracketValue);
		}
	}
	expressionStack.pop();
	tempStackReverse.push(expressionName);
	if (isOneBracket(expressionName) || isZeroBracket(expressionName))
	{
		try
		{
			expressionValue = calculateBracket(expressionName.substr(0, expressionName.size()));
			cell.bracketName = expressionName;
			cell.bracketValue = expressionValue;
			if (isNotRepeatInVector(table, cell)) table.push_back(cell);
		}
		catch (const std::runtime_error& e)
		{
			throw;
		}

	}
}

void iteration(std::string& expressionName, std::string& expressionValue, std::stack<std::string>& expressionStack,
			   std::stack<std::string>& tempStackReverse, Correspond& cell, std::vector<Correspond>& table)
{
	try
	{
		expressionName = expressionStack.top();
		if (isOneBracket(expressionName) && (expressionName[0] == '(') && (expressionName[expressionName.size() - 1] == ')'))
		{
			oneMainBracket(expressionName, expressionValue, cell, table, expressionStack);
		}
		else if (isZeroBracket(expressionName))
		{
			zeroMainBracket(expressionName, expressionValue, cell, table, expressionStack);
		}
		else
		{
			replaceExpressionName(expressionName, expressionValue, cell, table, expressionStack, tempStackReverse);
		}
	}
	catch (const std::exception& e)
	{
		throw;
	}
}

std::string calculateExpression(std::stack<std::string>& expressionStack)
{
	std::stack<std::string> tempStack, tempStackReverse;
	std::string expressionName, expressionValue;
	std::vector<Correspond> table;
	Correspond cell;
	do {
		try
		{
			iteration(expressionName, expressionValue, expressionStack, tempStackReverse, cell, table);
		}
		catch (const std::runtime_error& e)
		{
			throw;
		}
	} while (!expressionStack.empty());

	return expressionValue;
}