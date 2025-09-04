// main.cpp: определяет точку входа для приложения.
//

#include "../include/main.h"

int main()
{
	unsigned int testsTotal = 0, testsPassed = 0, testsFailed = 0;

	if (runAllTests(testsTotal, testsPassed, testsFailed))
	{
		try
		{
			char yn;
			bool cont;
			do
			{
				std::cout << "Enter expression to calculate(use only +-*/^()0123456789.):\n";
				std::string expression;
				std::cin >> expression;
				std::stack<std::string> expressionStack = bracketAnalyze(expression);
				std::cout << calculateExpression(expressionStack) << '\n';
				std::cout << "Continue? Enter y/n: ";
				bool err;
				do
				{
					std::cin >> yn;
					if (toupper(yn) == 'Y') { cont = true; err = false; }
					else if (toupper(yn) == 'N') { cont = false; err = false; }
					else
					{
						std::cout << "Invalid symbol! Enter y/n: ";
						err = true;
					}
				} while (err);
			} while (cont);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	return 0;
}