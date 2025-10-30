#include "../../include/Data/AnalysisCounter.h"

AnalysisCounter::AnalysisCounter() : successCount(0), errorCount(0), totalExpressions(0) {}

AnalysisCounter& AnalysisCounter::operator++()
{
    ++successCount;
    ++totalExpressions;
    return *this;
}

AnalysisCounter AnalysisCounter::operator++(int)
{
    AnalysisCounter temp = *this;
    ++(*this);
    return temp;
}

AnalysisCounter& AnalysisCounter::operator--()
{
    ++errorCount;
    ++totalExpressions;
    return *this;
}

AnalysisCounter AnalysisCounter::operator--(int)
{
    AnalysisCounter temp = *this;
    --(*this);
    return temp;
}

int AnalysisCounter::getSuccessCount() const { return successCount; }
int AnalysisCounter::getErrorCount() const { return errorCount; }
int AnalysisCounter::getTotalExpressions() const { return totalExpressions; }

void AnalysisCounter::reset()
{
    successCount = 0;
    errorCount = 0;
    totalExpressions = 0;
}