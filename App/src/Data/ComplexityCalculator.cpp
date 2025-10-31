#include "../../include/Data/ComplexityCalculator.h"

int ComplexityCalculator::calculateComplexity(const std::string& expression) const
{
    int complexity = 0;
    complexity += countOperators(expression) * 2;
    complexity += countBrackets(expression);
    if (hasComplexOperations(expression)) complexity += 5;
    return complexity;
}

int ComplexityCalculator::countOperators(const std::string& expression) const
{
    const std::string operators = "+-*/^";
    int count = 0;
    for (char c : expression) {
        if (operators.find(c) != std::string::npos) {
            count++;
        }
    }
    return count;
}

int ComplexityCalculator::countBrackets(const std::string& expression) const
{
    int count = 0;
    for (char c : expression) {
        if (c == '(' || c == ')') {
            count++;
        }
    }
    return count;
}

bool ComplexityCalculator::hasComplexOperations(const std::string& expression) const
{
    return expression.find('^') != std::string::npos ||
        expression.find('*') != std::string::npos ||
        expression.find('/') != std::string::npos;
}

std::string ComplexityCalculator::getComplexityLevel(const std::string& expression) const
{
    int complexity = calculateComplexity(expression);
    if (complexity <= 3) return "Low";
    else if (complexity <= 7) return "Medium";
    else return "High";
}