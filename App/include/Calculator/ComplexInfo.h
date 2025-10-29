#pragma once

#ifndef COMPLEXINFO_H
#define COMPLEXINFO_H

#include <vector>
#include <complex>

#include "CalculatorExpression.h"

class ComplexInfo : public CalculatorExpression
{
private:
    // Приватный конструктор
    ComplexInfo() = default;

    // Запрещаем копирование и присваивание
    ComplexInfo(const ComplexInfo&) = delete;
    ComplexInfo& operator=(const ComplexInfo&) = delete;

    // Данные
    std::complex<long double> principalValue;
    std::vector<std::complex<long double>> allRoots;
    std::vector<long double> realRoots, positiveRoots, negativeRoots;
    bool isComplex = false;

public:
    std::complex<long double> getPrincipalValue(){ return principalValue; }
    std::vector<std::complex<long double>> getAllRoots() { return allRoots; }
    std::vector<long double> getRealRoots() { return realRoots; }
    std::vector<long double> getPositiveRoots() { return positiveRoots; }
    std::vector<long double> getNegativeRoots() { return negativeRoots; }
    bool getIsComplex() { return isComplex; }

    // Статический метод для доступа к единственному экземпляру
    static ComplexInfo& getInstance()
    {
        static ComplexInfo instance;
        return instance;
    }

    // Метод для установки всех значений
    void set(
        std::complex<long double> pv,
        std::vector<std::complex<long double>> ar,
        std::vector<long double> rr,
        std::vector<long double> pr,
        std::vector<long double> nr,
        bool ic)
    {
        principalValue = pv;
        allRoots = ar;
        realRoots = rr;
        positiveRoots = pr;
        negativeRoots = nr;
        isComplex = ic;
    }

    // Метод для очистки данных
    void clear()
    {
        principalValue = std::complex<long double>(0.0, 0.0);
        allRoots.clear();
        realRoots.clear();
        positiveRoots.clear();
        negativeRoots.clear();
        isComplex = false;
    }
};

#endif // !COMPLEXINFO_H