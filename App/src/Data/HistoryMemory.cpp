#include "../../include/Data/HistoryMemory.h"

HistoryMemory* HistoryMemory::calculateAndSave(const std::string& expression)
{
    try {
        // Вычисляем выражение
        Calculator calc;
        std::stack<std::string> expressionStack = calc.bracketAnalyze(expression);
        std::string result = calc.calculateExpression(expressionStack);

        // Создаем запись для истории
        unsigned int recordNumber = getNextNumber();
        Record historyRecord = createCalculationRecord(expression, result, recordNumber);

        // Сохраняем в историю
        History::reserveData(historyRecord);

        // Также сохраняем в память (опционально, можно убрать если не нужно)
        Record memoryRecord = historyRecord;
        Memory::reserveData(memoryRecord);

        std::cout << "Calculation saved as record #" << recordNumber << std::endl;

    }
    catch (const std::exception& e) {
        // В случае ошибки сохраняем информацию об ошибке
        unsigned int recordNumber = getNextNumber();
        Record errorRecord;
        errorRecord.number = recordNumber;
        errorRecord.info.push_back("Expression: " + expression);
        errorRecord.info.push_back("Error: " + std::string(e.what()));
        errorRecord.info.push_back("Result: ERROR");

        History::reserveData(errorRecord);

        std::cout << "Error calculation saved as record #" << recordNumber << std::endl;
        throw; // Пробрасываем исключение дальше
    }

    return this;
}

Data* HistoryMemory::reserveData(Record data)
{
    // Обновляем данные в общем базовом классе Data
    if (data.number == 0) {
        data.number = getNextNumber();
    }
    else {
        currentNumber = std::max(currentNumber, data.number + 1);
    }

    this->data.push_back(data);

    // Сохраняем в историю с временной меткой
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    RecordHistory newrh = { data, now };
    rh.push_back(newrh);

    // Сохраняем в память
    MemoryCell cell;
    cell.record = data;
    cell.operator12 = ' ';
    mc.push_back(cell);

    return this;
}

Data* HistoryMemory::getData()
{
    return this;
}

Record HistoryMemory::createCalculationRecord(const std::string& expression,
    const std::string& result,
    unsigned int number) const
{
    Record record;
    record.number = number;
    record.info.push_back("Expression: " + expression);
    record.info.push_back("Result: " + result);

    return record;
}

void HistoryMemory::printCalculationHistory() const
{
    std::cout << "=== Calculation History (" << rh.size() << " records) ===" << std::endl;

    for (const auto& historyEntry : rh) {
        std::time_t time = std::chrono::system_clock::to_time_t(historyEntry.now);
        std::tm localTime;

#ifdef _WIN32
        localtime_s(&localTime, &time);
#else
        localtime_r(&time, &localTime);
#endif

        std::cout << "Record #" << historyEntry.record.number << ":\n";

        // Выводим только выражение и результат
        for (const auto& info : historyEntry.record.info) {
            if (info.find("Expression:") == 0 || info.find("Result:") == 0 || info.find("Error:") == 0) {
                std::cout << "  " << info << "\n";
            }
        }

        std::cout << "  Calculated at: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";
        std::cout << std::endl;
    }
}

void HistoryMemory::printCalculationByNumber(unsigned int number) const
{
    for (const auto& historyEntry : rh) {
        if (historyEntry.record.number == number) {
            std::time_t time = std::chrono::system_clock::to_time_t(historyEntry.now);
            std::tm localTime;

#ifdef _WIN32
            localtime_s(&localTime, &time);
#else
            localtime_r(&time, &localTime);
#endif

            std::cout << "=== Calculation Record #" << number << " ===" << std::endl;
            std::cout << "Record #" << historyEntry.record.number << ":\n";

            for (const auto& info : historyEntry.record.info) {
                if (info.find("Expression:") == 0 || info.find("Result:") == 0 || info.find("Error:") == 0) {
                    std::cout << "  " << info << "\n";
                }
            }

            std::cout << "  Calculated at: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";
            return;
        }
    }
    std::cout << "Calculation record #" << number << " not found!" << std::endl;
}

std::string HistoryMemory::getLastCalculationResult() const
{
    if (rh.empty()) {
        return "No calculations yet";
    }

    const auto& lastRecord = rh.back().record;
    for (const auto& info : lastRecord.info) {
        if (info.find("Result:") == 0) {
            return info.substr(8); // Возвращаем результат без "Result: "
        }
    }

    return "Result not found";
}