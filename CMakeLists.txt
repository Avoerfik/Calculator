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
    "src/main.cpp"
    "src/Testing.cpp"
    "src/Calculator.cpp"
    "src/Menu/Menu.cpp"
    "src/CalculatorComplex.cpp"
    "src/Menu/MenuInput.cpp"
    "src/Menu/MenuOutput.cpp"
)
add_executable(Calculator ${SOURCES})

# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Calculator "src/main.cpp" "include/main.h" "src/Calculator.cpp" "src/Testing.cpp" "include/Calculator.h" "include/Testing.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Calculator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
