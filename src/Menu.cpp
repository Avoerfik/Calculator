#include "../include/Menu.h"

Menu::Menu() : testsTotal(0), testsPassed(0), testsFailed(0)
{

}

Menu::~Menu()
{

}

void Menu::run()
{
    if (runAllTests(testsTotal, testsPassed, testsFailed))
    {
        try
        {
            std::string yn;
            bool cont;
            do
            {
                std::cout << "Enter expression to calculate(use only +-*/^()0123456789.):\n";
                std::string expression;
                std::getline(std::cin, expression);
                std::stack<std::string> expressionStack = bracketAnalyze(expression);
                std::cout << calculateExpression(expressionStack) << '\n';
                std::cout << "Continue? Enter y/n: ";
                bool err;
                do
                {
                    std::getline(std::cin, yn);
                    err = isCorrectChar(yn);
                    if (err)
                    {
                        if (toupper(yn[0]) == 'Y') { cont = true; err = false; }
                        else if (toupper(yn[0]) == 'N') { cont = false; err = false; }
                        else
                        {
                            std::cout << "Invalid symbol! Continue? Enter y/n: ";
                            err = true;
                        }
                    }
                    else
                    {
                        std::cout << "Continue? Enter y/n: ";
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
}

bool Menu::isCorrectChar(const std::string& input)
{
    if (input.empty())
    {
        std::cout << "Empty input! ";

        return false;
    }
    else if (input.size() != 1)
    {
        std::cout << "Enter one input character! ";

        return false;
    }

    else return true;
}