#pragma once

#ifndef MENUOUTPUT_H
#define MENUOUTPUT_H

#include <exception>

#include "Menu.h"
#include "ComplexInfo.h"

class MenuOutput : public Menu
{
public:
    MenuOutput();
    ~MenuOutput();
    
    void displayResult(const std::string& result);
    void displayMessage(const std::string& message);
    void displayError(const std::exception& e);
    void displayTestResults();
    void displayComplexResults();
    
private:
    void formatOutput(const std::string& content, const std::string& prefix = "");
};

#endif // MENUOUTPUT_H