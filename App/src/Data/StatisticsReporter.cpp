#include "../../include/Data/ExpressionAnalyzer.h"
#include "../../include/Data/ExpressionHistory.h"
#include <sstream>

// Реализация дружественной функции
std::string generateStatisticsReport(const ExpressionAnalyzer& analyzer, const ExpressionHistory& history)
{
    std::stringstream ss;
    ss << "=== Comprehensive Statistics Report ===\n";
    ss << "Expression Analysis:\n";
    ss << "  Total: " << analyzer.getTotalExpressions() << "\n";
    ss << "  Success: " << analyzer.getSuccessCount() << "\n";
    ss << "  Errors: " << analyzer.getErrorCount() << "\n";

    ss << "\nOperator Frequency:\n";
    auto freq = analyzer.getOperatorFrequency();
    for (const auto& [op, count] : freq) {
        ss << "  " << op << ": " << count << " times\n";
    }

    ss << "\nHistory Summary:\n";
    ss << "  Records: " << history.size() << "\n";
    ss << "  Avg Complexity: " << history.getAverageComplexity() << "\n";

    return ss.str();
}