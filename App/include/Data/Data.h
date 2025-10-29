#pragma once

#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

#include "../Engine.h"

struct Record
{
    std::vector<std::string> info;
    unsigned int number;
};

class Data : public Engine
{
public:
    Data() {
        this->data.reserve(1);
        currentNumber = 1;  // Начинаем с номера 1
    }
    Data(Record data) {
        this->data.push_back(data);
        currentNumber = data.number + 1;  // Продолжаем с следующего номера
    }
    virtual ~Data() = default;

    virtual Data* reserveData(Record data) = 0;
    virtual Data* getData() = 0;

protected:
    std::vector<Record> data;
    unsigned int currentNumber = 1;  // Счётчик номеров

    // Метод для получения следующего номера
    unsigned int getNextNumber() {
        return currentNumber++;
    }
};

#endif // !DATA_H