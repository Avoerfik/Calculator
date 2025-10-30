#include "../../include/Data/ExpressionHistory.h"
#include "../../include/Data/ExpressionAnalyzer.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

void ExpressionHistory::importFromAnalyzer(const ExpressionAnalyzer& analyzer)
{
    // Дружественный доступ к приватным данным analyzer
    auto stats = analyzer.stats;
    for (const auto& stat : stats) {
        AnalysisRecord record;
        record.timestamp = std::chrono::system_clock::now();
        record.stats = stat;
        record.wasSuccessful = true;
        records.push_back(record);
    }
}

void ExpressionHistory::addRecord(const AnalysisRecord& record)
{
    records.push_back(record);
}

void ExpressionHistory::clear()
{
    records.clear();
}

size_t ExpressionHistory::size() const
{
    return records.size();
}

std::vector<AnalysisRecord> ExpressionHistory::getRecentRecords(int count) const
{
    if (count <= 0 || records.empty()) {
        return std::vector<AnalysisRecord>();
    }

    if (count >= static_cast<int>(records.size())) {
        return records;
    }

    return std::vector<AnalysisRecord>(records.end() - count, records.end());
}

std::vector<AnalysisRecord> ExpressionHistory::getRecordsByComplexity(const std::string& level) const
{
    std::vector<AnalysisRecord> result;
    for (const auto& record : records) {
        if (record.stats.complexityLevel == level) {
            result.push_back(record);
        }
    }
    return result;
}

double ExpressionHistory::getAverageComplexity() const
{
    if (records.empty()) return 0.0;

    double sum = 0.0;
    for (const auto& record : records) {
        sum += record.stats.complexity;
    }
    return sum / records.size();
}

std::string ExpressionHistory::generateHistoryReport() const
{
    std::stringstream ss;
    ss << "=== Expression Analysis History ===\n";
    ss << "Total records: " << records.size() << "\n";
    ss << "Average complexity: " << getAverageComplexity() << "\n";

    if (!records.empty()) {
        ss << "Recent expressions:\n";
        auto recent = getRecentRecords(5);
        for (const auto& record : recent) {
            auto time = std::chrono::system_clock::to_time_t(record.timestamp);
            ss << "  " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                << " - " << record.stats.expression
                << " [" << record.stats.complexityLevel << "]\n";
        }
    }
    else {
        ss << "No records available.\n";
    }

    return ss.str();
}