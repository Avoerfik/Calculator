// include/Data/StatisticsReporter.h
#pragma once
#ifndef STATISTICSREPORTER_H
#define STATISTICSREPORTER_H

#include <string>
#include <sstream>

class ExpressionAnalyzer;
class ExpressionHistory;

// Объявление дружественной функции
std::string generateStatisticsReport(const ExpressionAnalyzer& analyzer, const ExpressionHistory& history);

#endif