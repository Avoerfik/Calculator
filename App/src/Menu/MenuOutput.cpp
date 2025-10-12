#include "../App/include/Menu/MenuOutput.h"

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
    if (!ci.getAllRoots().empty())
    {
        std::cout << "All roots:\n";
        for (const auto& i : ci.getAllRoots())
        {
            std::cout << std::to_string(i.real()) + " + " + std::to_string(i.imag()) + "i" << '\n';
        }
        if (!ci.getRealRoots().empty())
        {
            std::cout << "Real roots:\n";
            for (const auto& i : ci.getRealRoots())
            {
                std::cout << i << '\n';
            }
            if (!ci.getPositiveRoots().empty())
            {
                std::cout << "Positive Roots:\n";
                for (const auto& i : ci.getPositiveRoots())
                {
                    std::cout << i << '\n';
                }
            }
            if (!ci.getNegativeRoots().empty())
            {
                std::cout << "Negative Roots:\n";
                for (const auto& i : ci.getNegativeRoots())
                {
                    std::cout << i << '\n';
                }
            }
        }
        if (ci.getIsComplex()) std::cout << "Principal value: " << std::to_string(ci.getPrincipalValue().real()) + " + " + std::to_string(ci.getPrincipalValue().imag()) + "i" << '\n';
    }
}