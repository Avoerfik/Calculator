// include/Data/ComplexityCalculator.h
#pragma once
#ifndef COMPLEXITYCALCULATOR_H
#define COMPLEXITYCALCULATOR_H

#include "../Engine.h"
#include <string>

class ComplexityCalculator : public Engine
{
public:
    ComplexityCalculator() = default;

    int calculateComplexity(const std::string& expression) const;
    int countOperators(const std::string& expression) const;
    int countBrackets(const std::string& expression) const;
    bool hasComplexOperations(const std::string& expression) const;

    std::string getComplexityLevel(const std::string& expression) const;
};

#endif