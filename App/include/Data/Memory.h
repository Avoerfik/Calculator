#pragma once

#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <iostream>
#include <sstream>

#include "Data.h"

struct MemoryCell
{
    Record record;
    char operator12 = ' ';  // оператор: +, -, *, /, ^, или ' ' (пробел) для отсутствия оператора
};

class Memory : public Data
{
public:
    Memory() {};
    ~Memory() = default;

    // Новая версия с оператором
    Data* reserveData(const std::vector<std::string>& info, char nextOperator = ' ');
    // Старая версия для совместимости
    Data* reserveData(Record data) override;
    Data* getData() override;

    // Методы для работы с памятью
    std::string getCalculationString() const;
    void printMemory() const;
    const std::vector<MemoryCell>& getMemoryCells() const { return mc; }
    void clearMemory() { mc.clear(); data.clear(); currentNumber = 1; }
    bool isEmpty() const { return mc.empty(); }

private:
    std::vector<MemoryCell> mc;
};

#endif // !MEMORY_H