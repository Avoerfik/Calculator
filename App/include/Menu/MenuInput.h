#pragma once

#ifndef MENUINPUT_H
#define MENUINPUT_H

#include <iostream>

#include "Menu.h"

class MenuInput : protected Menu
{
public:
    MenuInput();
    ~MenuInput();

    std::string getExpression();
    bool getContinueChoice();
    int getCalculationRegime();

private:
    std::string readInput(const std::string& prompt);
};

#endif // MENUINPUT_H