#include "../App/include/Menu/MenuInput.h"


MenuInput::MenuInput() : Menu()
{

}

MenuInput::~MenuInput()
{

}

std::string MenuInput::getExpression()
{
    return readInput("Enter expression to calculate(use only +-*/^()0123456789.):\n");
}

bool MenuInput::getContinueChoice()
{
    std::string yn;
    bool err;
    do
    {
        yn = readInput("Continue? Enter y/n: ");
        err = isCorrectChar(yn);
        if (err)
        {
            if (toupper(yn[0]) == 'Y') { return true; }
            else if (toupper(yn[0]) == 'N') { return false; }
            else
            {
                std::cout << "Invalid symbol! ";
                err = true;
            }
        }
        else
        {
            err = true;
        }
    } while (err);

    return false;
}

bool MenuInput::getSaveToMemoryChoice()
{
    std::string yn;
    bool err;
    do
    {
        yn = readInput("Save result to memory? Enter y/n: ");
        err = isCorrectChar(yn);
        if (err)
        {
            if (toupper(yn[0]) == 'Y') { return true; }
            else if (toupper(yn[0]) == 'N') { return false; }
            else
            {
                std::cout << "Invalid symbol! ";
                err = true;
            }
        }
        else
        {
            err = true;
        }
    } while (err);

    return false;
}

std::string MenuInput::readInput(const std::string& prompt)
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int MenuInput::getCalculationRegime()
{
    do
    {
        std::cout << "Choose calculation regime:\n";
        std::cout << "1. Mathematical expression calculator\n";
        std::cout << "2. Matrix calculator\n";
        std::cout << "3. Show history\n";
        std::cout << "4. Calculate Memory\n";
        std::cout << "0. Exit\n";
        std::string input;
        std::getline(std::cin, input);
        if (isCorrectChar(input) &&
            ((input[0] == '0')
                || (input[0] == '1')
                || (input[0] == '2')
                || (input[0] == '3')
                || (input[0] == '4')))
            return std::stoi(input);
        std::cout << "Enter only 0, 1, 2 or 3!\n";
    } while (true);
}

Matrix MenuInput::getMatrix()
{
    Matrix matrix;
    std::cout << "Enter matrix:\n";
    std::cin >> matrix;
    std::cout << "Matrix is:\n";
    std::cout << matrix;
    return matrix;
}

char MenuInput::getMatrixOperator()
{
    do
    {
        std::cout << "Enter operator:\n";
        std::string input;
        std::getline(std::cin, input);
        if (isCorrectChar(input) && (input[0] == '+' || input[0] == '-' || input[0] == '*'))
            return input[0];
        std::cout << "Enter only (+-*):\n";
    } while (true);
}

char MenuInput::getMemoryOperator()
{
    do
    {
        std::cout << "Enter operator:\n";
        std::string input;
        std::getline(std::cin, input);
        if (isCorrectChar(input) &&
            (input[0] == '+' ||
                input[0] == '-' ||
                input[0] == '*' ||
                input[0] == '/' || 
                input[0] == '^' || 
                input[0] == ' '))
            return input[0];
        std::cout << "Enter only (+-*/^ ):\n";
    } while (true);
}

int MenuInput::getMatrixRegime()
{
    do
    {
        std::cout << "Choose matrix regime:\n1. Multiple matrix to matrix\n2. Multiple scalar to matrix\n";
        std::string input;
        std::getline(std::cin, input);
        if (isCorrectChar(input) && ((input[0] == '1') || (input[0] == '2')))
            return std::stoi(input);
        std::cout << "Enter only 1 or 2!\n";
    } while (true);
}