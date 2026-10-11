#include "../App/include/Menu/Menu.h"
#include "../App/include/Menu/MenuInput.h"
#include "../App/include/Menu/MenuOutput.h"

Menu::Menu() : testsTotal(0), testsPassed(0), testsFailed(0),
complexityCalculator(nullptr)
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

        bool exitMenu = true;
        bool cont;
        do
        {
            int regime = inputHandler.getCalculationRegime();
            switch (regime)
            {
            case 0:
                exitMenu = false;
                outputHandler.displayMessage("");
                break;
            case 1:
                do
                {
                    try
                    {
                        std::string expression = inputHandler.getExpression();

                        

                        std::stack<std::string> expressionStack = bracketAnalyze(expression);
                        std::string result = calculateExpression(expressionStack);

                        outputHandler.displayResult(result);
                        outputHandler.displayComplexResults();
                        outputHandler.displayMessage("");
                    }
                    catch (const std::exception& e)
                    {
                        MenuOutput outputHandler;
                        outputHandler.displayError(e);
                        outputHandler.displayMessage("");
                    }
                    cont = inputHandler.getContinueChoice();
                } while (cont);
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                break;
            case 5:
                break;
            }
        } while (exitMenu);
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

bool Menu::isCorrectInt(const std::string& input)
{
    const std::string numbers = "0123456789";
    for (const auto& i : input)
    {
        if (numbers.find(i) == std::string::npos)
            return false;
    }
    return true;
}