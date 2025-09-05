#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stack>
#include <locale.h>

std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateExpression(std::stack<std::string>& expressionStack);

bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed);

class Menu
{
public:
    Menu();
    ~Menu();
    void run();

private:
    unsigned int testsTotal, testsPassed, testsFailed;
    inline bool isCorrectChar(const std::string& input);
};

#endif // !MENU_H