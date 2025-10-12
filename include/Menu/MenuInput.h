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
    bool getSaveToMemoryChoice();
    int getCalculationRegime();
    Matrix getMatrix();
    char getMatrixOperator();
    char getMemoryOperator();
    int getMatrixRegime();

private:
    std::string readInput(const std::string& prompt);
};

#endif // MENUINPUT_H