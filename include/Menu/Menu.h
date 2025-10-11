#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stack>

#include "Matrix.h"

std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateExpression(std::stack<std::string>& expressionStack);

bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed);

class Menu
{
public:
    Menu();
    ~Menu();
    void run();

protected:
    unsigned int testsTotal, testsPassed, testsFailed;
    bool isCorrectChar(const std::string& input);
    bool isCorrectInt(const std::string& input);
    
};

#endif // !MENU_H