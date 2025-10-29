#pragma once

#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "../Calculator/CalculatorExpression.h"

std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateExpression(std::stack<std::string>& expressionStack);

class Testing : public CalculatorExpression
{
public:
	bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed);

private:
	using standartTest = bool (Testing::*)(const std::string&, const std::string&, const std::string&, const unsigned int&);
	using specifiedTest = bool (Testing::*)(const std::string&, const std::string&, const std::string&, const unsigned int&);

	struct TestCallStandart
	{
		standartTest func;
		std::string expression;
		std::string expected;
		std::string testName;
		unsigned int testNumber;
	};

	struct TestCallSpecified
	{
		specifiedTest func;
		std::string expression;
		std::string testName;
		std::string exceptionName;
		unsigned int testNumber;
	};


	bool runTest(const std::string& expression, const std::string& expected, const std::string& testName, const unsigned int& testNumber);
	bool runSpecifiedTest(const std::string& expression, const std::string& testName,
		const std::string& exceptionName, const unsigned int& testNumber);
	void runStandartTestCount(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed,
		std::vector<TestCallStandart>& vectorStandartTest, const std::string& expression,
		const std::string& expected, const std::string& testName, unsigned int& testNumber);
	void runSpecifiedTestCount(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed,
		std::vector<TestCallSpecified>& vectorSpecifiedTest, const std::string& expression,
		const std::string& testName, const std::string& exceptionName, unsigned int& testNumber);

};

#endif // !TESTING_H