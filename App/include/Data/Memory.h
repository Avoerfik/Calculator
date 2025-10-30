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
    char operator12 = ' ';
};

class Memory : public virtual Data  // ДОБАВЛЕНО virtual
{
public:
    Memory() {};
    ~Memory() = default;

    Data* reserveData(const std::vector<std::string>& info, char nextOperator = ' ');
    Data* reserveData(Record data) override;
    Data* getData() override;

    std::string getCalculationString() const;
    void printMemory() const;
    const std::vector<MemoryCell>& getMemoryCells() const { return mc; }
    void clearMemory() { mc.clear(); data.clear(); currentNumber = 1; }
    bool isEmpty() const { return mc.empty(); }

protected:  // Изменено с private на protected для доступа в HistoryMemory
    std::vector<MemoryCell> mc;
};

#endif // !MEMORY_H