#include "../include/Menu/Menu.h"
#include "../include/Menu/MenuInput.h"
#include "../include/Menu/MenuOutput.h"

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
        MenuInput inputHandler;
        MenuOutput outputHandler;

        bool cont;
        do
        {
            try
            {
                std::string expression = inputHandler.getExpression();
                std::stack<std::string> expressionStack = bracketAnalyze(expression);
                std::string result = calculateExpression(expressionStack);
                outputHandler.displayResult(result);
                outputHandler.displayComplexResults();
            }
            catch (const std::exception& e)
            {
                MenuOutput outputHandler;
                outputHandler.displayError(e);
            }
            cont = inputHandler.getContinueChoice();
        } while (cont);
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