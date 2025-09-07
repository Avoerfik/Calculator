#include "../include/Menu/MenuInput.h"
#include <iostream>

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