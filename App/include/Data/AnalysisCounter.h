#pragma once
#ifndef ANALYSISCOUNTER_H
#define ANALYSISCOUNTER_H

#include "../Engine.h"

class AnalysisCounter : public Engine
{
private:
    int successCount;
    int errorCount;
    int totalExpressions;

public:
    AnalysisCounter();

    // Перегрузка инкремента/декремента
    AnalysisCounter& operator++();    // Префиксный инкремент
    AnalysisCounter operator++(int);  // Постфиксный инкремент  
    AnalysisCounter& operator--();    // Префиксный декремент
    AnalysisCounter operator--(int);  // Постфиксный декремент

    // Геттеры
    int getSuccessCount() const;
    int getErrorCount() const;
    int getTotalExpressions() const;
    void reset();
};

#endif