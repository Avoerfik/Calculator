#include "../App/include/Menu/Menu.h"
#include "../App/include/Menu/MenuInput.h"
#include "../App/include/Menu/MenuOutput.h"

// ДОБАВИТЬ ВСЕ НЕОБХОДИМЫЕ ВКЛЮЧЕНИЯ
#include "../../include/Data/ExpressionAnalyzer.h"
#include "../../include/Data/ExpressionHistory.h"
#include "../../include/Data/AnalysisCounter.h"
#include "../../include/Data/ComplexityCalculator.h"
#include "../../include/Data/StatisticsReporter.h"

Menu::Menu() : testsTotal(0), testsPassed(0), testsFailed(0),
expressionAnalyzer(nullptr), expressionHistory(nullptr),
complexityCalculator(nullptr)
{
    initializeAnalyzers();
}

Menu::~Menu()
{
    // ОСВОБОДИТЬ ПАМЯТЬ
    if (expressionAnalyzer != nullptr) {
        delete expressionAnalyzer;
    }
    if (expressionHistory != nullptr) {
        delete expressionHistory;
    }
    if (complexityCalculator != nullptr) {
        delete complexityCalculator;
    }
}

void Menu::initializeAnalyzers()
{
    // СОЗДАТЬ ОБЪЕКТЫ АНАЛИЗАТОРОВ
    complexityCalculator = new ComplexityCalculator();
    expressionAnalyzer = new ExpressionAnalyzer(complexityCalculator);
    expressionHistory = new ExpressionHistory();
}

void Menu::run()
{
    if (runAllTests(testsTotal, testsPassed, testsFailed))
    {
        MenuInput inputHandler;
        MenuOutput outputHandler;
        History mathHistory;
        Memory mathMemory;
        HistoryMemory historyMemory;

        bool exitMenu = true;
        bool cont;
        do
        {
            int regime = inputHandler.getCalculationRegime();
            switch (regime)
            {
            case 0:
                exitMenu = false;
                outputHandler.displayMessage("");
                break;
            case 1:
                do
                {
                    try
                    {
                        std::string expression = inputHandler.getExpression();

                        // ЗАМЕР ВРЕМЕНИ ВЫЧИСЛЕНИЯ ДЛЯ СТАТИСТИКИ
                        auto startTime = std::chrono::high_resolution_clock::now();

                        std::stack<std::string> expressionStack = bracketAnalyze(expression);
                        std::string result = calculateExpression(expressionStack);

                        auto endTime = std::chrono::high_resolution_clock::now();
                        double calcTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

                        // АНАЛИЗ ВЫРАЖЕНИЯ И ЗАПИСЬ В СТАТИСТИКУ
                        if (expressionAnalyzer != nullptr) {
                            expressionAnalyzer->analyzeExpression(expression, calcTime);
                            expressionAnalyzer->recordSuccess();
                        }

                        // Сохраняем в обычную историю
                        mathHistory.reserveData({ expression + " = " + result });

                        bool saveToMemory = inputHandler.getSaveToMemoryChoice();
                        if (saveToMemory)
                        {
                            char operator12 = inputHandler.getMemoryOperator();
                            mathMemory.reserveData({ result }, operator12);
                        }
                        outputHandler.displayResult(result);
                        outputHandler.displayComplexResults();
                        outputHandler.displayMessage("");
                    }
                    catch (const std::exception& e)
                    {
                        // ЗАПИСЬ ОШИБКИ В СТАТИСТИКУ
                        if (expressionAnalyzer != nullptr) {
                            expressionAnalyzer->recordError();
                        }

                        MenuOutput outputHandler;
                        outputHandler.displayError(e);
                        outputHandler.displayMessage("");
                    }
                    cont = inputHandler.getContinueChoice();
                } while (cont);
                break;
            case 2:
                do
                {
                    try
                    {
                        Matrix matrix1 = inputHandler.getMatrix();
                        char operator12 = inputHandler.getMatrixOperator();
                        if (operator12 == '*')
                        {
                            int matrixRegime = inputHandler.getMatrixRegime();
                            if (matrixRegime == 1)
                            {
                                Matrix matrix2 = inputHandler.getMatrix();
                                Matrix result(matrix1.cols(), matrix2.rows());
                                result = matrix1 * matrix2;
                                std::cout << "Result matrix is:\n";
                                std::cout << result;
                            }
                            else
                            {
                                std::string expression = inputHandler.getExpression();
                                std::stack<std::string> expressionStack = bracketAnalyze(expression);
                                std::string scalar = calculateExpression(expressionStack);
                                Matrix result(matrix1.rows(), matrix1.cols());
                                result = std::stoi(scalar) * matrix1;
                                std::cout << "Result matrix is:\n";
                                std::cout << result;
                            }
                        }
                        else
                        {
                            Matrix result(matrix1.rows(), matrix1.cols());
                            Matrix matrix2 = inputHandler.getMatrix();
                            if (operator12 == '+') result = matrix1 + matrix2;
                            else result = matrix1 - matrix2;
                            std::cout << "Result matrix is:\n";
                            std::cout << result;
                        }
                        outputHandler.displayMessage("");
                    }
                    catch (const std::exception& e)
                    {
                        MenuOutput outputHandler;
                        outputHandler.displayError(e);
                        outputHandler.displayMessage("");
                    }
                    cont = inputHandler.getContinueChoice();
                } while (cont);
                break;
            case 3:
                // Показываем меню выбора типа истории
                mathHistory.printAllHistory();
                historyMemory.printCalculationHistory();
                outputHandler.displayMessage("");
                break;
            case 4:
                try
                {
                    std::string calculationString = mathMemory.getCalculationString();
                    if (calculationString.empty()) {
                        outputHandler.displayMessage("Memory is empty");
                    }
                    else {
                        std::stack<std::string> expressionStack = bracketAnalyze(calculationString);
                        std::string result = calculateExpression(expressionStack);

                        // Сохраняем вычисление из памяти в HistoryMemory
                        historyMemory.calculateAndSave(calculationString);

                        outputHandler.displayResult(result);
                        mathMemory.clearMemory();
                    }
                    outputHandler.displayMessage("");
                }
                catch (const std::exception& e)
                {
                    MenuOutput outputHandler;
                    outputHandler.displayError(e);
                    outputHandler.displayMessage("");
                }
                break;
                // НОВЫЙ ПУНКТ МЕНЮ ДЛЯ СТАТИСТИКИ
            case 5:
                displayStatisticsMenu();
                break;
            }
        } while (exitMenu);
    }
}

// РЕАЛИЗАЦИЯ МЕТОДОВ СТАТИСТИКИ
void Menu::displayStatisticsMenu()
{
    MenuInput inputHandler;
    MenuOutput outputHandler;

    bool exitStatsMenu = true;
    do
    {
        std::cout << "\n=== Expression Statistics ===\n";
        std::cout << "1. Show Basic Statistics\n";
        std::cout << "2. Show Operator Frequency\n";
        std::cout << "3. Show Complexity Analysis\n";
        std::cout << "4. Show Comprehensive Report\n";
        std::cout << "5. Reset Statistics\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choose option: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0") {
            exitStatsMenu = false;
        }
        else if (choice == "1") {
            showExpressionStatistics();
        }
        else if (choice == "2") {
            showOperatorFrequency();
        }
        else if (choice == "3") {
            showComplexityAnalysis();
        }
        else if (choice == "4") {
            showComprehensiveReport();
        }
        else if (choice == "5") {
            resetStatistics();
        }
        else {
            outputHandler.displayMessage("Invalid choice! Please try again.");
        }

    } while (exitStatsMenu);
}

void Menu::showExpressionStatistics()
{
    if (expressionAnalyzer == nullptr) {
        std::cout << "Statistics analyzer not initialized!\n";
        return;
    }

    std::cout << "\n=== Expression Statistics ===\n";
    std::cout << "Total expressions analyzed: " << expressionAnalyzer->getTotalExpressions() << "\n";
    std::cout << "Successful calculations: " << expressionAnalyzer->getSuccessCount() << "\n";
    std::cout << "Errors encountered: " << expressionAnalyzer->getErrorCount() << "\n";
    std::cout << "Success rate: "
        << (expressionAnalyzer->getTotalExpressions() > 0 ?
            (expressionAnalyzer->getSuccessCount() * 100.0 / expressionAnalyzer->getTotalExpressions()) : 0)
        << "%\n";
}

void Menu::showOperatorFrequency()
{
    if (expressionAnalyzer == nullptr) {
        std::cout << "Statistics analyzer not initialized!\n";
        return;
    }

    auto frequency = expressionAnalyzer->getOperatorFrequency();
    std::cout << "\n=== Operator Frequency ===\n";

    if (frequency.empty()) {
        std::cout << "No operators analyzed yet.\n";
        return;
    }

    for (const auto& [op, count] : frequency) {
        std::cout << "Operator '" << op << "': " << count << " times\n";
    }
}

void Menu::showComplexityAnalysis()
{
    if (expressionAnalyzer == nullptr) {
        std::cout << "Statistics analyzer not initialized!\n";
        return;
    }

    auto stats = expressionAnalyzer->getStats();
    std::cout << "\n=== Complexity Analysis ===\n";

    if (stats.empty()) {
        std::cout << "No expressions analyzed yet.\n";
        return;
    }

    std::map<std::string, int> complexityLevels;
    int totalComplexity = 0;

    for (const auto& stat : stats) {
        complexityLevels[stat.complexityLevel]++;
        totalComplexity += stat.complexity;
    }

    std::cout << "Average complexity: " << (totalComplexity / static_cast<double>(stats.size())) << "\n";
    std::cout << "Complexity distribution:\n";
    for (const auto& [level, count] : complexityLevels) {
        std::cout << "  " << level << ": " << count << " expressions\n";
    }
}

void Menu::showComprehensiveReport()
{
    if (expressionAnalyzer == nullptr || expressionHistory == nullptr) {
        std::cout << "Statistics analyzer not initialized!\n";
        return;
    }

    // Импортируем данные в историю для генерации отчета
    expressionHistory->importFromAnalyzer(*expressionAnalyzer);

    // Используем дружественную функцию для генерации отчета
    std::string report = generateStatisticsReport(*expressionAnalyzer, *expressionHistory);
    std::cout << "\n" << report << "\n";
}

void Menu::resetStatistics()
{
    if (expressionAnalyzer != nullptr) {
        delete expressionAnalyzer;
        expressionAnalyzer = new ExpressionAnalyzer(complexityCalculator);
    }
    if (expressionHistory != nullptr) {
        delete expressionHistory;
        expressionHistory = new ExpressionHistory();
    }
    std::cout << "Statistics reset successfully!\n";
}

// СУЩЕСТВУЮЩИЕ МЕТОДЫ БЕЗ ИЗМЕНЕНИЙ
bool Menu::isCorrectChar(const std::string& input)
{
    if (input.empty())
    {
        std::cout << "Empty input! ";
        return false;
    }
    else if (input.size() != 1)
    {
        std::cout << "Enter one input character! ";
        return false;
    }
    else return true;
}

bool Menu::isCorrectInt(const std::string& input)
{
    const std::string numbers = "0123456789";
    for (const auto& i : input)
    {
        if (numbers.find(i) == std::string::npos)
            return false;
    }
    return true;
}