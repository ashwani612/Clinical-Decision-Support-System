#include "CDSS.h"
#include <exception>
#include <iostream>

int main() {
    try {
        CDSS system;
        system.run();
    } catch (const std::exception& error) {
        std::cerr << "Application error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
