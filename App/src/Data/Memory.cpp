#include "../../include/Data/Memory.h"

// Новая версия с оператором
Data* Memory::reserveData(const std::vector<std::string>& info, char nextOperator)
{
    Record record;
    record.info = info;
    record.number = getNextNumber();

    MemoryCell cell;
    cell.record = record;
    cell.operator12 = nextOperator;

    this->data.push_back(record);
    mc.push_back(cell);

    return this;
}

// Старая версия для совместимости
Data* Memory::reserveData(Record data)
{
    if (data.number == 0) {
        data.number = getNextNumber();
    }
    else {
        currentNumber = std::max(currentNumber, data.number + 1);
    }

    MemoryCell cell;
    cell.record = data;
    cell.operator12 = ' ';  // по умолчанию нет оператора

    this->data.push_back(data);
    mc.push_back(cell);

    return this;
}

Data* Memory::getData()
{
    return this;
}

// Метод для получения строки расчета (просто объединяет все результаты и операторы)
std::string Memory::getCalculationString() const
{
    if (mc.empty()) {
        return "";
    }

    std::stringstream ss;

    for (size_t i = 0; i < mc.size(); ++i) {
        const MemoryCell& cell = mc[i];

        // Добавляем результат из первой строки info
        if (!cell.record.info.empty()) {
            ss << "(" + cell.record.info[0] + ")";
        }

        // Добавляем оператор, если он есть и это не последняя ячейка
        if (cell.operator12 != ' ' && i < mc.size() - 1) {
            ss << cell.operator12;
        }
    }

    return ss.str();
}

// Метод для вывода содержимого памяти
void Memory::printMemory() const
{
    std::cout << "=== Memory Contents (" << mc.size() << " cells) ===" << std::endl;

    for (size_t i = 0; i < mc.size(); ++i) {
        const MemoryCell& cell = mc[i];

        std::cout << "Cell #" << cell.record.number << ":\n";
        for (const auto& info : cell.record.info) {
            std::cout << "  " << info << "\n";
        }

        if (cell.operator12 != ' ') {
            std::cout << "  Next operator: " << cell.operator12 << "\n";
        }
        else {
            std::cout << "  No next operator\n";
        }

        std::cout << std::endl;
    }

    // Показываем строку для расчета
    std::string calculationString = getCalculationString();
    if (!calculationString.empty()) {
        std::cout << "Calculation string: " << calculationString << std::endl;
    }
}