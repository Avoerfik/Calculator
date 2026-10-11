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
        std::cout << "0. Exit\n";
        std::string input;
        std::getline(std::cin, input);
        if (isCorrectChar(input) &&
            ((input[0] == '0')
                || (input[0] == '1')))
            return std::stoi(input);
        std::cout << "Enter only 0, 1!\n";
    } while (true);
}