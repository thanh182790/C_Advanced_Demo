#include <iostream>
#include "config.h"
#include "system.h"

void runAppDemo(void)
{
    std::cout << "=============================================\n";
    std::cout << "[C++] runAppDemo(): calling C system layer...\n";
    std::cout << "=============================================\n";
    System_init();
    for (int i = 0; i < NUM_DEMO; ++i)
    {
        System_run();
    }

    std::cout << "\n=============================================\n";
    std::cout << "[C++] runAppDemo(): done.\n";
    std::cout << "=============================================\n";
}

int main()
{
    runAppDemo();
    return 0;
}
