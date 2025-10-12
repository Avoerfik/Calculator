#include "../App/include/Menu/Menu.h"
#include "../App/include/Menu/MenuInput.h"
#include "../App/include/Menu/MenuOutput.h"

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
        History mathHistory;
        Memory mathMemory;

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
                        mathHistory.reserveData({ expression + " = " + result });
                        bool saveToMemory = inputHandler.getSaveToMemoryChoice();
                        if (saveToMemory)
                        {
                            char operator12 = inputHandler.getMemoryOperator();
                            mathMemory.reserveData({ result }, operator12);
                        }
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
                break;
            case 2:
                do
                {
                    try
                    {
                        Matrix matrix1 = inputHandler.getMatrix();
                        char operator12 = inputHandler.getMatrixOperator();
                        if (operator12 == '*')
                        {
                            int matrixRegime = inputHandler.getMatrixRegime();
                            if (matrixRegime == 1)
                            {
                                Matrix matrix2 = inputHandler.getMatrix();
                                Matrix result(matrix1.cols(), matrix2.rows());
                                result = matrix1 * matrix2;
                                std::cout << result;
                            }
                            else
                            {
                                std::string expression = inputHandler.getExpression();
                                std::stack<std::string> expressionStack = bracketAnalyze(expression);
                                std::string scalar = calculateExpression(expressionStack);
                                Matrix result(matrix1.rows(), matrix1.cols());
                                result = std::stoi(scalar) * matrix1;
                                std::cout << result;
                            }
                        }
                        else
                        {
                            Matrix result(matrix1.rows(), matrix1.cols());
                            Matrix matrix2 = inputHandler.getMatrix();
                            if (operator12 == '+') result = matrix1 + matrix2;
                            else result = matrix1 - matrix2;
                            std::cout << result;
                        }
                    }
                    catch (const std::exception& e)
                    {
                        MenuOutput outputHandler;
                        outputHandler.displayError(e);
                    }
                    cont = inputHandler.getContinueChoice();
                } while (cont);
                break;
            case 3:
                mathHistory.printAllHistory();
                break;
            case 4:
                try
                {
                    std::string calculationString = mathMemory.getCalculationString();
                    std::stack<std::string> expressionStack = bracketAnalyze(calculationString);
                    std::string result = calculateExpression(expressionStack);
                    outputHandler.displayResult(result);
                    mathMemory.clearMemory();
                }
                catch (const std::exception& e)
                {
                    MenuOutput outputHandler;
                    outputHandler.displayError(e);
                }
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