#pragma once
#ifndef EXPRESSIONHISTORY_H
#define EXPRESSIONHISTORY_H

#include "../Engine.h"
#include "ExpressionStats.h"
#include <vector>
#include <chrono>

class ExpressionAnalyzer;

struct AnalysisRecord
{
    std::chrono::system_clock::time_point timestamp;
    ExpressionStats stats;
    bool wasSuccessful;
};

class ExpressionHistory : public Engine
{
private:
    std::vector<AnalysisRecord> records;

public:
    ExpressionHistory() = default;

    // Дружественный доступ к ExpressionAnalyzer
    void importFromAnalyzer(const ExpressionAnalyzer& analyzer);

    // Методы работы с историей
    void addRecord(const AnalysisRecord& record);
    void clear();
    size_t size() const;

    // Аналитические методы
    std::vector<AnalysisRecord> getRecentRecords(int count = 10) const;
    std::vector<AnalysisRecord> getRecordsByComplexity(const std::string& level) const;
    double getAverageComplexity() const;

    // Генерация отчётов
    std::string generateHistoryReport() const;
};

// Дружественная функция
std::string generateStatisticsReport(const ExpressionAnalyzer& analyzer, const ExpressionHistory& history);

#endif