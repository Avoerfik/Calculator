#include "CalculatorComplex.h"

// Внутренние функции
std::vector<std::complex<long double>> CalculatorComplex::getAllRoots(const std::complex<long double>& base, const std::complex<long double>& power)
{
    std::vector<std::complex<long double>> allRoots;
    std::vector<std::complex<long double>> uniqueRoots;

    long double radius = std::abs(base);
    long double theta = std::arg(base);
    long double lnRadius = std::log(radius);

    int maxIterations = 10;

    for (int k = 0; k < maxIterations; k++)
    {
        std::complex<long double> lnBase(lnRadius, theta + 2 * PI * k);
        std::complex<long double> exponent = power * lnBase;
        std::complex<long double> result = std::exp(exponent);

        allRoots.push_back(result);
        if (uniqueRoots.empty()) uniqueRoots.push_back(result);
        else
        {
            bool isUnique = true;
            for (size_t i = 0; i < uniqueRoots.size(); i++)
            {
                if ((std::abs(uniqueRoots[i].real() - result.real()) < EPSILON)
                    && (std::abs(uniqueRoots[i].imag() - result.imag()) < EPSILON)) { isUnique = false; break; }
            }

            if (isUnique) uniqueRoots.push_back(result);
        }
    }

    return uniqueRoots;
}

std::vector<long double> CalculatorComplex::getRealRoots(const std::vector<std::complex<long double>>& roots)
{
    std::vector<long double> realRoots;
    for (const auto& i : roots)
    {
        if (std::abs(i.imag()) < EPSILON) realRoots.push_back(i.real());
    }

    return realRoots;
}

// Внешние функции
std::vector<std::complex<long double>> getAllRoots(const std::complex<long double>& base, const std::complex<long double>& power)
{
	CalculatorComplex calc;

	return calc.getAllRoots(base, power);
}

std::vector<long double> getRealRoots(const std::vector<std::complex<long double>>& roots)
{
    CalculatorComplex calc;

    return calc.getRealRoots(roots);
}