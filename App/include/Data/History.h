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

class History : public virtual Data
{
public:
    History() {};
    ~History() = default;

    Data* reserveData(const std::vector<std::string>& info);
    Data* reserveData(Record data) override;
    Data* getData() override;

    const std::vector<RecordHistory>& getHistory() const { return rh; }
    size_t getHistorySize() const { return rh.size(); }

    void printRecordHistory(const RecordHistory& rh) const;
    void printAllHistory() const;
    void printRecordByNumber(unsigned int number) const;

protected:  // Изменено с private на protected для доступа в HistoryMemory
    std::vector<RecordHistory> rh;
};

#endif // !HISTORY_H