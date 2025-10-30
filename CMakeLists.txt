# CMakeList.txt: проект CMake для Calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Calculator")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
set(SOURCES
    "App/src/main.cpp"
    "App/src/Testing/Testing.cpp"
    "App/src/Calculator/Calculator.cpp"
    "App/src/Menu/Menu.cpp"
    "App/src/Calculator/CalculatorComplex.cpp"
    "App/src/Menu/MenuInput.cpp"
    "App/src/Menu/MenuOutput.cpp"
    "App/src/Matrix/Matrix.cpp"
    "App/src/Data/History.cpp"
    "App/src/Data/Memory.cpp"
    "App/include/Engine.h"
)
add_executable(Calculator ${SOURCES} "App/include/Data/HistoryMemory.h" "App/src/Data/HistoryMemory.cpp" "App/include/Data/AnalysisCounter.h" "App/include/Data/ComplexityCalculator.h" "App/include/Data/ExpressionAnalyzer.h" "App/include/Data/ExpressionHistory.h" "App/src/Data/AnalysisCounter.cpp" "App/src/Data/ComplexityCalculator.cpp" "App/src/Data/ExpressionAnalyzer.cpp" "App/src/Data/ExpressionHistory.cpp" "App/include/Data/StatisticsReporter.h" "App/src/Data/StatisticsReporter.cpp" "App/include/Data/ExpressionStats.h")

# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Calculator "src/main.cpp" "include/main.h" "src/Calculator.cpp" "src/Testing.cpp" "include/Calculator.h" "include/Testing.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Calculator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
