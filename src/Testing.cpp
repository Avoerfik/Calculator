#include "../include/Testing.h"

bool runTest(const std::string& expression, const std::string& expected, const std::string& testName, const unsigned int& testNumber)
{
	bool isPassed;
	try
	{
		std::stack<std::string> expressionStack = bracketAnalyze(expression);
		std::string result = calculateExpression(expressionStack);

		std::cout << "№" << testNumber << ":\n";
		std::cout << "Test: " << testName << '\n';
		std::cout << "Expression: " << expression << '\n';
		std::cout << "Expected: " << expected << '\n';
		std::cout << "Got: " << result << '\n';

		if (result == expected)
		{
			std::cout << "✓ PASSED\n";
			isPassed = true;
		}
		else
		{
			std::cout << "✗ FAILED\n";
			isPassed = false;
		}
		std::cout << "----------------------\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Test: " << testName << " - EXCEPTION: " << e.what() << '\n';
		std::cout << "----------------------\n";
		isPassed = false;
	}
	return isPassed;
}

bool runSpecifiedTest(const std::string& expression, const std::string& testName, const std::string& exceptionName, const unsigned int& testNumber)
{
	bool isPassed;
	std::cout << "№" << testNumber << ":\n";
	try
	{
		std::stack<std::string> expressionStack = bracketAnalyze(expression);
		std::string result = calculateExpression(expressionStack);
		std::cout << "Test: " << testName << " - FAILED (should have thrown exception)\n";
		std::cout << "Result was: " << result << '\n';
		isPassed = false;
	}
	catch (const std::runtime_error& e)
	{
		if (std::string(e.what()).find(exceptionName) != std::string::npos)
		{
			std::cout << "Test: " << testName << " - PASSED (correctly caught format error)\n";
			isPassed = true;
		}
		else
		{
			std::cout << "Test: " << testName << " - FAILED (wrong exception: " << e.what() << ")\n";
			isPassed = false;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Test: " << testName << " - FAILED (unexpected exception: " << e.what() << ")\n";
		isPassed = false;
	}
	std::cout << "----------------------\n";
	return isPassed;
}

void runStandartTestCount(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed, std::vector<TestCallStandart>& vectorStandartTest,
	const std::string& expression, const std::string& expected, const std::string& testName, unsigned int& testNumber)
{
	if (runTest(expression, expected, testName, testNumber))
	{
		++testsPassed;
	}
	else
	{
		++testsFailed;
		vectorStandartTest.push_back({ runTest, expression, expected, testName, testNumber });
	}
	++testsTotal;
	++testNumber;
}

void runSpecifiedTestCount(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed, std::vector<TestCallSpecified>& vectorSpecifiedTest,
	const std::string& expression, const std::string& testName, const std::string& exceptionName, unsigned int& testNumber)
{
	if (runSpecifiedTest(expression, testName, exceptionName, testNumber))
	{
		++testsPassed;
	}
	else
	{
		++testsFailed;
		vectorSpecifiedTest.push_back({ runSpecifiedTest, expression, testName, exceptionName, testNumber });
	}
	++testNumber;
	++testsTotal;
}

bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed)
{
	testsTotal = 0, testsPassed = 0, testsFailed = 0;
	unsigned int testNumber = 1;

	std::vector<TestCallStandart> vectorStandartTest;
	std::vector<TestCallSpecified> vectorSpecifiedTest;

	std::cout << "----------------------\n";
	std::cout << "Start testing\n";
	std::cout << "----------------------\n";

	// 1-2. Выражения с множеством +-
	/* №1  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "+-+5", "-5", "Multiple plus-minus 1", testNumber);
	/* №2  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-+-+5", "5", "Multiple plus-minus 2", testNumber);

	// 3-8. Выражения вида +1 -1 +0,9 -0,9 +,9 -,9
	/* №3  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "+1", "1", "Positive integer", testNumber);
	/* №4  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-1", "-1", "Negative integer", testNumber);
	/* №5  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "+0.9", "0.9", "Positive decimal", testNumber);
	/* №6  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-0.9", "-0.9", "Negative decimal", testNumber);
	/* №7  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "+.9", ".9", "Positive decimal without zero", testNumber);
	/* №8  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-.9", "-.9", "Negative decimal without zero", testNumber);

	// 9-17. Выражения с умножением и делением всех вариантов
	/* №9  */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*3", "6", "Positive multiplication", testNumber);
	/* №10 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-2*3", "-6", "Negative * positive", testNumber);
	/* №11 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*-3", "-6", "Positive * negative", testNumber);
	/* №12 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-2*-3", "6", "Negative * negative", testNumber);
	/* №13 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "6/2", "3", "Positive division", testNumber);
	/* №14 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-6/2", "-3", "Negative / positive", testNumber);
	/* №15 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "6/-2", "-3", "Positive / negative", testNumber);
	/* №16 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-6/-2", "3", "Negative / negative", testNumber);
	/* №17 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "5/2", "2.500000", "Decimal division", testNumber);

	// 18-24. Выражения с операторами одинакового приоритета
	/* №18 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1", "1", "Single number", testNumber);
	/* №19 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1+2", "3", "Simple addition", testNumber);
	/* №20 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1+2-3", "0", "Addition and subtraction", testNumber);
	/* №21 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "5-3+2", "4", "Subtraction and addition", testNumber);
	/* №22 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10-5-3", "2", "Multiple subtractions", testNumber);
	/* №23 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1+2+3+4", "10", "Multiple additions", testNumber);
	/* №24 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10-1-2-3", "4", "Complex subtraction chain", testNumber);

	// 25-31. Выражения со скобками и операторами одинакового приоритета
	/* №25 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(1+2)", "3", "Simple brackets", testNumber);
	/* №26 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(1+2)-3", "0", "Brackets and operation", testNumber);
	/* №27 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "5-(3+2)", "0", "Brackets subtraction", testNumber);
	/* №28 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(5-3)+2", "4", "Brackets addition", testNumber);
	/* №29 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(10-5)-3", "2", "Nested operations 1", testNumber);
	/* №30 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10-(5-3)", "8", "Nested operations 2", testNumber);
	/* №31 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "((1+2)-3)+4", "4", "Multiple brackets", testNumber);

	// 22-34. Проверка деления на 0
	/* №32 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "5/0", "Division by zero integer", "Divide by zero", testNumber);
	/* №33 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "5.0/0", "Division by zero decimal", "Divide by zero", testNumber);
	/* №34 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "(5+3)/(2-2)", "Division by zero in expression", "Divide by zero", testNumber);

	// 35. Проверка избыточного количества точек
	/* №35 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "1.2.3", "Multiple dots test", "Invalid data format!", testNumber);

	// 36-40. Выражения с целочисленным и нецелочисленным делением
	/* №36 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "8/4", "2", "Integer division", testNumber);
	/* №37 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "8/3", "2.666667", "Non-integer division", testNumber);
	/* №38 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10/4", "2.500000", "Decimal division 2", testNumber);
	/* №39 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-8/4", "-2", "Negative integer division", testNumber);
	/* №40 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-8/3", "-2.666667", "Negative non-integer division", testNumber);


	// 41-49. Выражения с операторами разного приоритета
	/* №41 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1+2*3", "7", "Addition and multiplication", testNumber);
	/* №42 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*3+1", "7", "Multiplication and addition", testNumber);
	/* №43 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "6/2+3", "6", "Division and addition", testNumber);
	/* №44 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1+6/2", "4", "Addition and division", testNumber);
	/* №45 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*3-4/2", "4", "Mixed operations 1", testNumber);
	/* №46 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10-2*3", "4", "Mixed operations 2", testNumber);
	/* №47 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*3*4", "24", "Multiple multiplications", testNumber);
	/* №48 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "24/2/3", "4", "Multiple divisions", testNumber);
	/* №49 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2+3*4-6/2", "11", "Complex mixed operations", testNumber);

	// 50-58. Выражения со скобками и операторами разного приоритета
	/* №50 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(1+2)*3", "9", "Brackets change priority 1", testNumber);
	/* №51 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*(3+1)", "8", "Brackets change priority 2", testNumber);
	/* №52 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(6-3)*(4+2)", "18", "Complex brackets 1", testNumber);
	/* №53 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(10+2)/(3+1)", "3", "Complex brackets 2", testNumber);
	/* №54 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2*(3+4*(5-1))", "38", "Nested brackets", testNumber);
	/* №55 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "((1+2)*3)-4", "5", "Multiple nested brackets", testNumber);
	/* №56 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(2+3)*(4-1)/(2+1)", "5", "Complex expression with brackets", testNumber);
	/* №57 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "10/(2+3)*4", "8", "Brackets in denominator", testNumber);
	/* №58 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "(5*2)+(3*4)-(6/2)", "19", "Multiple bracket groups", testNumber);

	// 59-68. Дополнительные стандартные тесты
	/* №59 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "0", "0", "Zero", testNumber);
	/* №60 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "0.0", "0.0", "Zero decimal", testNumber);
	/* №61 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "-0", "0", "Negative zero", testNumber);
	/* №62 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "2.5*2", "5.000000", "Decimal multiplication", testNumber);
	/* №63 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "0.1+0.2", "0.300000", "Small decimals addition", testNumber);
	/* №64 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "1000000*1000000", "1000000000000", "Large numbers", testNumber);
	/* №65 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "11*-+-+-5", "-55", "More signs after product 1", testNumber);
	/* №66 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "11*+-+-5", "55", "More signs after product 2", testNumber);
	/* №67 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "55/-+-+-5", "-11", "More signs after divide 1", testNumber);
	/* №68 */ runStandartTestCount(testsTotal, testsPassed, testsFailed, vectorStandartTest, "55/+-+-5", "11", "More signs after divide 2", testNumber);

	// 69-89. Дополнительные специфичные тесты
	/* №69 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "abc", "Invalid Symbols", "Invalid Symbols", testNumber);
	/* №70 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "+-*/.", "No Number", "No Number", testNumber);
	/* №71 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "*+12", "Invalid data format!", "Invalid data format!", testNumber);
	/* №72 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "/+12", "Invalid data format!", "Invalid data format!", testNumber);
	/* №73 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52+*1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №74 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52-*1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №75 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52+/1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №76 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52-/1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №77 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52+", "Invalid data format!", "Invalid data format!", testNumber);
	/* №78 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52-", "Invalid data format!", "Invalid data format!", testNumber);
	/* №79 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52*", "Invalid data format!", "Invalid data format!", testNumber);
	/* №80 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "52/", "Invalid data format!", "Invalid data format!", testNumber);
	/* №81 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "1(5)", "Invalid data format!", "Invalid data format!", testNumber);
	/* №82 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "(5)1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №83 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "5))*((1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №84 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "5)*(1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №85 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "()+1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №86 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "(1*(+1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №87 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, ")1*)+1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №88 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "(0).1", "Invalid data format!", "Invalid data format!", testNumber);
	/* №89 */ runSpecifiedTestCount(testsTotal, testsPassed, testsFailed, vectorSpecifiedTest, "0.(1)", "Invalid data format!", "Invalid data format!", testNumber);

	std::cout << "\n----------------------\n";
	std::cout << "Testing completed!\n";
	std::cout << "Total Tests: " << testsTotal << '\n';
	std::cout << "Passed Tests: " << testsPassed << '\n';
	std::cout << "Failed Tests: " << testsFailed << '\n';
	std::cout << "----------------------\n";
	if (testsFailed == 0)
	{
		std::cout << "\nAll tests passed!\n\n";
		return true;
	}
	else
	{
		std::cout << "\nFailed tests:\n";
		std::cout << "----------------------\n";
		for (const auto& i : vectorStandartTest)
		{
			i.func(i.expression, i.expected, i.testName, i.testNumber);
		}
		for (const auto& i : vectorSpecifiedTest)
		{
			i.func(i.expression, i.testName, i.exceptionName, i.testNumber);
		}
		std::cout << '\n';
		return false;
	}
}