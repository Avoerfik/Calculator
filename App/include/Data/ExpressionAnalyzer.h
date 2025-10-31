#pragma once
#ifndef EXPRESSIONANALYZER_H
#define EXPRESSIONANALYZER_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "../Engine.h"
#include "AnalysisCounter.h"
#include "ComplexityCalculator.h"
#include "ExpressionStats.h"

class ExpressionHistory;

class ExpressionAnalyzer : public Engine
{
private:
    AnalysisCounter counter;
    ComplexityCalculator* complexityCalc; //Агрегация
    std::vector<ExpressionStats> stats;
    std::map<char, int> operatorFrequency;

    void analyzeOperators(const std::string& expression);
    void updateOperatorFrequency(const std::string& expression);

public:
    ExpressionAnalyzer();
    ExpressionAnalyzer(ComplexityCalculator* calc);
    virtual ~ExpressionAnalyzer();  // Убрать удаление complexityCalc для агрегации

    void analyzeExpression(const std::string& expression, double calcTime = 0.0);
    void recordSuccess();
    void recordError();

    // Геттеры для статистики
    int getTotalExpressions() const;
    int getSuccessCount() const;
    int getErrorCount() const;
    std::map<char, int> getOperatorFrequency() const;
    std::vector<ExpressionStats> getStats() const;

    // Дружественные объявления
    friend class ExpressionHistory;
    friend std::string generateStatisticsReport(const ExpressionAnalyzer& analyzer, const ExpressionHistory& history);
};

#endif