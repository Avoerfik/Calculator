// include/Data/ExpressionStats.h
#pragma once
#ifndef EXPRESSIONSTATS_H
#define EXPRESSIONSTATS_H

#include <string>

struct ExpressionStats
{
    std::string expression;
    int complexity;
    std::string complexityLevel;
    int operatorCount;
    bool hasComplexOps;
    double calculationTime;

    // Новые поля для анализа операторов
    bool hasConsecutiveOperators;
    bool startsWithBinaryOperator;
    bool endsWithOperator;
    bool potentialDivisionByZero;
    int numberCount;
    double operandOperatorRatio;
};

#endif