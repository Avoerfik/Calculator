// main.cpp: определяет точку входа для приложения.
//

#include "main.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Menu menu;
    menu.run();
    return 0;
}