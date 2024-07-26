#include <iostream>
#include <vector>

#include "object_searcher.hpp"

int main() {
    std::vector<int> numbers = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10};
    std::vector<int> numbers2 = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    
    SEARCHER::Finder<int> finder(numbers);
    SEARCHER::Finder<int> finder2(numbers2);

    std::vector<int*> results = finder.findAll<10>(8);
    std::vector<int*> results2 = finder2.findAll<10>(0);    

    for (const auto& res : results) {
        std::cout << *res << " ";
    }
    std::cout << "\n";

    for (const auto& res : results2) {
        std::cout << *res << " ";
    }
    std::cout << "\n";
    return 0;
}
