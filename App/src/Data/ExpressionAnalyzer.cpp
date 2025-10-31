#include "../../include/Data/ExpressionAnalyzer.h"

// Конструктор по умолчанию - без создания ComplexityCalculator
ExpressionAnalyzer::ExpressionAnalyzer() : complexityCalc(nullptr) {}

// Конструктор с агрегацией - принимаем готовый объект
ExpressionAnalyzer::ExpressionAnalyzer(ComplexityCalculator* calc) : complexityCalc(calc) {}

// Деструктор - НЕ удаляем complexityCalc (агрегация)
ExpressionAnalyzer::~ExpressionAnalyzer()
{
    // complexityCalc НЕ удаляем - это агрегация!
}

void ExpressionAnalyzer::analyzeOperators(const std::string& expression)
{
    // Анализ паттернов использования операторов
    const std::string operators = "+-*/^";

    // 1. Проверка на последовательные операторы (кроме унарных +- в начале)
    bool hasConsecutiveOps = false;
    for (size_t i = 1; i < expression.length(); ++i) {
        if (operators.find(expression[i]) != std::string::npos &&
            operators.find(expression[i - 1]) != std::string::npos) {
            // Исключаем случаи унарных операторов: "+5", "-3", "(-2)", "+(5)"
            if (!(expression[i] == '+' || expression[i] == '-') ||
                (i > 0 && expression[i - 1] != '(' && expression[i - 1] != ' ')) {
                hasConsecutiveOps = true;
                break;
            }
        }
    }

    // 2. Проверка на операторы в начале/конце (кроме унарных +-)
    bool startsWithBinaryOp = false;
    bool endsWithOp = false;

    if (!expression.empty()) {
        char firstChar = expression[0];
        if (operators.find(firstChar) != std::string::npos &&
            firstChar != '+' && firstChar != '-') {
            startsWithBinaryOp = true;
        }

        char lastChar = expression[expression.length() - 1];
        if (operators.find(lastChar) != std::string::npos) {
            endsWithOp = true;
        }
    }

    // 3. Анализ баланса операторов и операндов
    int operatorCount = 0;
    int numberCount = 0;
    const std::string numbers = "0123456789";

    for (char c : expression) {
        if (operators.find(c) != std::string::npos) {
            operatorCount++;
        }
        if (numbers.find(c) != std::string::npos) {
            numberCount++;
        }
    }

    // 4. Проверка на использование оператора деления с нулем
    bool hasDivisionByZeroPattern = false;
    size_t divPos = expression.find('/');
    if (divPos != std::string::npos && divPos + 1 < expression.length()) {
        // Ищем следующий символ после '/'
        size_t nextPos = divPos + 1;
        // Пропускаем пробелы и унарные +-
        while (nextPos < expression.length() &&
            (expression[nextPos] == ' ' || expression[nextPos] == '+' || expression[nextPos] == '-')) {
            nextPos++;
        }

        if (nextPos < expression.length()) {
            // Проверяем, не идет ли сразу ноль
            if (expression[nextPos] == '0') {
                // Но исключаем случаи типа "0.5"
                if (nextPos + 1 >= expression.length() || expression[nextPos + 1] != '.') {
                    hasDivisionByZeroPattern = true;
                }
            }
        }
    }

    // 5. Анализ приоритетов операторов
    bool hasHighPriorityOps = expression.find('^') != std::string::npos;
    bool hasMediumPriorityOps = expression.find('*') != std::string::npos ||
        expression.find('/') != std::string::npos;
    bool hasLowPriorityOps = expression.find('+') != std::string::npos ||
        expression.find('-') != std::string::npos;

    // 6. Сохраняем результаты анализа (можно добавить в структуру ExpressionStats)
    // Пока просто выводим в консоль для отладки
    std::cout << "\n=== Operator Analysis ===\n";
    std::cout << "Expression: " << expression << "\n";
    std::cout << "Consecutive operators: " << (hasConsecutiveOps ? "YES" : "NO") << "\n";
    std::cout << "Starts with binary operator: " << (startsWithBinaryOp ? "YES" : "NO") << "\n";
    std::cout << "Ends with operator: " << (endsWithOp ? "YES" : "NO") << "\n";
    std::cout << "Operator count: " << operatorCount << "\n";
    std::cout << "Number count: " << numberCount << "\n";
    std::cout << "Operand/Operator ratio: " << (operatorCount > 0 ? static_cast<double>(numberCount) / operatorCount : 0) << "\n";
    std::cout << "Potential division by zero: " << (hasDivisionByZeroPattern ? "WARNING" : "NO") << "\n";
    std::cout << "High priority ops (^): " << (hasHighPriorityOps ? "YES" : "NO") << "\n";
    std::cout << "Medium priority ops (*,/): " << (hasMediumPriorityOps ? "YES" : "NO") << "\n";
    std::cout << "Low priority ops (+,-): " << (hasLowPriorityOps ? "YES" : "NO") << "\n";

    // 7. Проверка на сложные операторные конструкции
    bool hasComplexOperatorPatterns = hasConsecutiveOps || startsWithBinaryOp || endsWithOp || hasDivisionByZeroPattern;
    if (hasComplexOperatorPatterns) {
        std::cout << "WARNING: Expression has complex operator patterns that might cause errors!\n";
    }
}

void ExpressionAnalyzer::analyzeExpression(const std::string& expression, double calcTime)
{
    ExpressionStats stats;
    stats.expression = expression;
    stats.calculationTime = calcTime;

    // Проверяем, что complexityCalc установлен (агрегация)
    if (complexityCalc) {
        stats.complexity = complexityCalc->calculateComplexity(expression);
        stats.complexityLevel = complexityCalc->getComplexityLevel(expression);
        stats.operatorCount = complexityCalc->countOperators(expression);
        stats.hasComplexOps = complexityCalc->hasComplexOperations(expression);
    }
    else {
        // Запасной вариант, если complexityCalc не установлен
        stats.complexity = 1;
        stats.complexityLevel = "Unknown";
        stats.operatorCount = 0;
        stats.hasComplexOps = false;
    }

    // Вызываем анализ операторов
    analyzeOperators(expression);

    this->stats.push_back(stats);
    updateOperatorFrequency(expression);
    ++counter; // Увеличиваем счётчик успешных анализов
}

void ExpressionAnalyzer::recordSuccess()
{
    ++counter;
}

void ExpressionAnalyzer::recordError()
{
    --counter;
}

void ExpressionAnalyzer::updateOperatorFrequency(const std::string& expression)
{
    const std::string operators = "+-*/^";
    for (char op : operators) {
        size_t count = std::count(expression.begin(), expression.end(), op);
        if (count > 0) {
            operatorFrequency[op] += count;
        }
    }
}

// Геттеры
int ExpressionAnalyzer::getTotalExpressions() const { return counter.getTotalExpressions(); }
int ExpressionAnalyzer::getSuccessCount() const { return counter.getSuccessCount(); }
int ExpressionAnalyzer::getErrorCount() const { return counter.getErrorCount(); }
std::map<char, int> ExpressionAnalyzer::getOperatorFrequency() const { return operatorFrequency; }
std::vector<ExpressionStats> ExpressionAnalyzer::getStats() const { return stats; }