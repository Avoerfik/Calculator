#pragma once

#ifndef CALCULATORCOMPLEX_H
#define CALCULATORCOMPLEX_H

#include "Calculator.h"

class CalculatorComplex : private Calculator
{
private:
	const long double E = 2.7182818284590452;
	const long double PI = 3.1415926535897932;
	const long double EPSILON = 1e-4;

public:
	std::vector<std::complex<long double>> getAllRoots(const std::complex<long double>& base,
		const std::complex<long double>& power);
	inline std::vector<long double> getRealRoots(const std::vector<std::complex<long double>>& roots);
};

#endif // !CALCULATORCOMPLEX_H
