#include "jshell.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "READY\n";
    std::string s;
    std::cin >> s;
    std::cout << "GOT: " << s << "\n";

    runShell();
    return 0;
}
