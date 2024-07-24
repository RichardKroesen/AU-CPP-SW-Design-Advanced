#include <iostream>
#include <vector>
#include "linear_search.hpp"

int main() {
    std::vector<int> intArr = {10, 25, 37, 42, 54};
    int intKey = 42;
    int intResult = linearSearch(intArr, intKey);

    if (intResult != -1) {
        std::cout << "Element found at index " << intResult << std::endl;
    } else {
        std::cout << "Element not found in the array" << std::endl;
    }

    std::vector<std::string> stringArr = {"apple", "banana", "cherry", "date"};
    std::string stringKey = "cherry";
    int stringResult = linearSearch(stringArr, stringKey);

    if (stringResult != -1) {
        std::cout << "Element found at index " << stringResult << std::endl;
    } else {
        std::cout << "Element not found in the array" << std::endl;
    }

    return 0;
}
