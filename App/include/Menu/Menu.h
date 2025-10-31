#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <stack>
#include <chrono>

#include "../Engine.h"
#include "../Matrix/Matrix.h"
#include "../Data/History.h"
#include "../Data/Memory.h"
#include "../Data/HistoryMemory.h"

class ExpressionAnalyzer;
class ExpressionHistory;
class ComplexityCalculator;

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

    // НОВЫЕ МЕТОДЫ для работы со статистикой
    void initializeAnalyzers();
    void displayStatisticsMenu();
    void showExpressionStatistics();
    void showOperatorFrequency();
    void showComplexityAnalysis();
    void showComprehensiveReport();
    void resetStatistics();

private:
    // НОВЫЕ УКАЗАТЕЛИ на анализаторы
    ExpressionAnalyzer* expressionAnalyzer;
    ExpressionHistory* expressionHistory;
    ComplexityCalculator* complexityCalculator;
};

#endif // !MENU_H