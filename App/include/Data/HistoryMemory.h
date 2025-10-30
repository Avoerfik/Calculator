#pragma once

#ifndef HISTORYMEMORY_H
#define HISTORYMEMORY_H

#include "History.h"
#include "Memory.h"
#include "../Calculator/Calculator.h"

class HistoryMemory : public History, public Memory
{
public:
    HistoryMemory() {};
    ~HistoryMemory() = default;

    // Используем общий счетчик из Data
    unsigned int getNextNumber() {
        return currentNumber++;
    }

    // Основной метод для вычисления и сохранения выражения
    HistoryMemory* calculateAndSave(const std::string& expression);

    // Переопределение методов
    Data* reserveData(Record data) override;
    Data* getData() override;

    // Методы для работы с историей вычислений
    void printCalculationHistory() const;
    void printCalculationByNumber(unsigned int number) const;
    std::string getLastCalculationResult() const;

private:
    // Вспомогательный метод для создания записи из результата вычисления
    Record createCalculationRecord(const std::string& expression,
        const std::string& result,
        unsigned int number) const;
};

#endif // !HISTORYMEMORY_H