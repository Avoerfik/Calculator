#include "../include/Menu/MenuOutput.h"
#include <iostream>

MenuOutput::MenuOutput() : Menu()
{

}

MenuOutput::~MenuOutput()
{

}

void MenuOutput::displayResult(const std::string& result)
{
    formatOutput("Result: " + result, ">>> ");
}

void MenuOutput::displayMessage(const std::string& message)
{
    formatOutput(message);
}

void MenuOutput::displayError(const std::exception& e)
{
    formatOutput("Error: " + std::string(e.what()), "!!! ");
}

void MenuOutput::displayTestResults()
{
    formatOutput("Tests completed: Total=" + std::to_string(testsTotal) +
        ", Passed=" + std::to_string(testsPassed) +
        ", Failed=" + std::to_string(testsFailed));
}

void MenuOutput::formatOutput(const std::string& content, const std::string& prefix)
{
    std::cout << prefix << content << '\n';
}

void MenuOutput::displayComplexResults()
{
    ComplexInfo& ci = ComplexInfo::getInstance();
    if (!ci.allRoots.empty())
    {
        std::cout << "All roots:\n";
        for (const auto& i : ci.allRoots)
        {
            std::cout << std::to_string(i.real()) + " + " + std::to_string(i.imag()) + "i" << '\n';
        }
        if (!ci.realRoots.empty())
        {
            std::cout << "Real roots:\n";
            for (const auto& i : ci.realRoots)
            {
                std::cout << i << '\n';
            }
            if (!ci.positiveRoots.empty())
            {
                std::cout << "Positive Roots:\n";
                for (const auto& i : ci.positiveRoots)
                {
                    std::cout << i << '\n';
                }
            }
            if (!ci.negativeRoots.empty())
            {
                std::cout << "Negative Roots:\n";
                for (const auto& i : ci.negativeRoots)
                {
                    std::cout << i << '\n';
                }
            }
        }
        if (ci.isComplex) std::cout << "Principal value: " << std::to_string(ci.principalValue.real()) + " + " + std::to_string(ci.principalValue.imag()) + "i" << '\n';
    }
}