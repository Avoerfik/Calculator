#include "../App/include/History.h"
#include <iostream>
#include <ctime>
#include <iomanip>

// Новая версия - принимает только информацию, номер генерируется автоматически
Data* History::reserveData(const std::vector<std::string>& info)
{
    Record record;
    record.info = info;
    record.number = getNextNumber();  // Автоматически получаем следующий номер

    this->data.push_back(record);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    RecordHistory newrh = { record, now };
    rh.push_back(newrh);

    return this;
}

// Старая версия для совместимости
Data* History::reserveData(Record data)
{
    // Если номер не установлен, устанавливаем автоматически
    if (data.number == 0) {
        data.number = getNextNumber();
    }
    else {
        // Обновляем счетчик, если номер предоставлен вручную
        currentNumber = std::max(currentNumber, data.number + 1);
    }

    this->data.push_back(data);
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    RecordHistory newrh = { data, now };
    rh.push_back(newrh);

    return this;
}

Data* History::getData()
{
    return this;
}

// Метод для вывода одной записи истории
void History::printRecordHistory(const RecordHistory& rh) const
{
    std::time_t time = std::chrono::system_clock::to_time_t(rh.now);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::cout << "Record #" << rh.record.number << ":\n";
    for (const auto& info : rh.record.info) {
        std::cout << "  " << info << "\n";
    }
    std::cout << "  Calculated at: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << std::endl;
}

// Метод для вывода всей истории
void History::printAllHistory() const
{
    std::cout << "=== Full History (" << rh.size() << " records) ===" << std::endl;
    for (const auto& historyEntry : rh) {
        printRecordHistory(historyEntry);
    }
}

// Метод для вывода записи по номеру
void History::printRecordByNumber(unsigned int number) const
{
    for (const auto& historyEntry : rh) {
        if (historyEntry.record.number == number) {
            std::cout << "=== Record #" << number << " ===" << std::endl;
            printRecordHistory(historyEntry);
            return;
        }
    }
    std::cout << "Record #" << number << " not found!" << std::endl;
}