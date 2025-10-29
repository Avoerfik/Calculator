#pragma once

#ifndef HISTORY_H
#define HISTORY_H

#include <chrono>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "Data.h"

struct RecordHistory
{
    Record record;
    std::chrono::system_clock::time_point now;
};

class History : public Data
{
public:
    History() {};
    ~History() = default;

    // Новая перегруженная версия без параметра number
    Data* reserveData(const std::vector<std::string>& info);
    // Старая версия для совместимости
    Data* reserveData(Record data) override;
    Data* getData() override;

    // Метод для доступа к истории
    const std::vector<RecordHistory>& getHistory() const { return rh; }
    size_t getHistorySize() const { return rh.size(); }

    // Методы для вывода истории
    void printRecordHistory(const RecordHistory& rh) const;
    void printAllHistory() const;
    void printRecordByNumber(unsigned int number) const;

private:
    std::vector<RecordHistory> rh;
};

#endif // !HISTORY_H