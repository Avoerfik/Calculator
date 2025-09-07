#pragma once

#ifndef MENUINPUT_H
#define MENUINPUT_H

#include "Menu.h"

class MenuInput : public Menu
{
public:
    MenuInput();
    ~MenuInput();

    std::string getExpression();
    bool getContinueChoice();

private:
    std::string readInput(const std::string& prompt);
};

#endif // MENUINPUT_H