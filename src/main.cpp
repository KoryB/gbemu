#include <iostream>
#include "main.h"

int main() {
    const auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    std::cout << Foo << std::endl;

    return 0;
}