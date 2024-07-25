#include <iostream>
#include <optional>

int main(int argc, char *argv[]) {
    std::optional<int> opt = 42;

    std::cout << "Hello Toolchain Exercise!" << std::endl;
    std::cout << "Test of C++ 17: " << std::endl;

    if (opt) {
        std::cout << "Optional has value: " << *opt << std::endl;
    } else {
        std::cout << "Optional is empty" << std::endl;
    }
    
    return 0;
}