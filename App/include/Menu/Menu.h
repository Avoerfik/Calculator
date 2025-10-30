#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stack>

#include "../Engine.h"
#include "../Matrix/Matrix.h"
#include "../Data/History.h"
#include "../Data/Memory.h"

std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateExpression(std::stack<std::string>& expressionStack);

bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed);

class Menu : public Engine
{
public:
    Menu();
    virtual ~Menu();
    void run();

protected:
    unsigned int testsTotal, testsPassed, testsFailed;
    bool isCorrectChar(const std::string& input);
    bool isCorrectInt(const std::string& input);
    
};

#endif // !MENU_H