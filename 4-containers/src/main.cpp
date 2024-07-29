#include <iostream>
#include <vector>

#include "object_searcher.hpp"
#include "synch_queue.hpp"

std::vector<int> generateAndSort(int N) {
    std::vector<int> sequence;
    sequence.reserve(N);

    std::srand(std::time(0));

    // Generate N random integers
    for (int i = 0; i < N; ++i) {
        auto element = std::rand() % 100;
        sequence.push_back(element); 
        for (auto j : sequence) {
            std::sort(sequence.begin(), sequence.end());
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    return sequence;
}

void removeElementsByUserInput(std::vector<int>& sequence) {
    while (!sequence.empty()) {
        int position;
        std::cout << "Enter the position to remove (0 to " << sequence.size() - 1 << "): ";
        std::cin >> position;

        if (position < 0 || position >= sequence.size()) {
            std::cout << "Invalid position. Please try again." << std::endl;
            continue;
        }

        sequence.erase(sequence.begin() + position); 

        if (sequence.empty()) {
            std::cout << "Sequence is now empty." << std::endl;
        } else {
            std::cout << "Current sequence: ";
            for (const int& num : sequence) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    int N;
    std::cout << "Enter the number of random integers to generate: ";
    std::cin >> N;
    auto sequence = generateAndSort(N);
    removeElementsByUserInput(sequence);
    return 0;
}