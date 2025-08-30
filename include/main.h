// main.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <stack>

std::stack<std::string> bracketAnalyze(const std::string& expression);
std::string calculateExpression(std::stack<std::string>& expressionStack);

bool runAllTests(unsigned int& testsTotal, unsigned int& testsPassed, unsigned int& testsFailed);

#endif // !MAIN_H

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.