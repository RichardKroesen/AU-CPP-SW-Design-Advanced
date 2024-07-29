#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <type_traits>

template <typename Container, size_t N = 0>
Container generateAndSort(size_t N_runtime) {
    Container sequence;
    std::srand(std::time(0)); // Seed for random number generation

    if constexpr (std::is_array_v<Container>) {
        // For std::array, use the array's size
        N = sequence.size();
    }

    // Generate N random integers
    for (int i = 0; (i < N) || (i < N_runtime); ++i) {
        auto element = std::rand() % 100;
        if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::list<int>>) {
            sequence.push_back(element);
        } else if constexpr (std::is_same_v<Container, std::array<int, N>>) {
            sequence[i] = element;
        }

        // Print the current sequence
        if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::list<int>>) {
            for (const auto& j : sequence) {
                std::cout << j << " ";
            }
        } else if constexpr (std::is_same_v<Container, std::array<int, N>>) {
            for (int j = 0; j <= i; ++j) {
                std::cout << sequence[j] << " ";
            }
        }
        std::cout << std::endl;
    }

    // Sort the sequence
    if constexpr (std::is_same_v<Container, std::vector<int>> || (std::is_same_v<Container, std::array<int, N>>)) {
        std::sort(sequence.begin(), sequence.end());
    } else if constexpr (std::is_same_v<Container, std::list<int>>) {
        sequence.sort();
    }

    return sequence;
}

template <typename Container>
void removeElementsByUserInput(Container& sequence) {
    while (!sequence.empty()) {
        int position;
        std::cout << "Enter the position to remove (0 to " << sequence.size() - 1 << "): ";
        std::cin >> position;

        if (position < 0 || position >= sequence.size()) {
            std::cout << "Invalid position. Please try again." << std::endl;
            continue;
        }

        if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::list<int>>) {
            auto it = sequence.begin();
            std::advance(it, position);
            sequence.erase(it); // Remove the element at the specified position
        } else if constexpr (std::is_array_v<Container>) {
            // For std::array, shift elements to the left
            for (size_t i = position; i < sequence.size() - 1; ++i) {
                sequence[i] = sequence[i + 1];
            }
            sequence[sequence.size() - 1] = 0; // Set the last element to 0
        }

        if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::list<int>>) {
            if (sequence.empty()) {
                std::cout << "Sequence is now empty." << std::endl;
                break;
            }
        } else if constexpr (std::is_array_v<Container>) {
            if (position == sequence.size() - 1) {
                std::cout << "All elements have been processed." << std::endl;
                break;
            }
        }

        std::cout << "Current sequence: ";
        for (const auto& num : sequence) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int N;
    std::cout << "Enter the number of random integers to generate: ";
    std::cin >> N;

    // Using std::vector
    std::vector<int> vectorSequence = generateAndSort<std::vector<int>>(N);
    std::cout << "Initial sorted vector sequence: ";
    for (const int& num : vectorSequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // removeElementsByUserInput(vectorSequence);

    // Using std::list
    std::list<int> listSequence = generateAndSort<std::list<int>>(N);
    std::cout << "Initial sorted list sequence: ";
    for (const int& num : listSequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // removeElementsByUserInput(listSequence);

    // Using std::array (with fixed size 10)
    constexpr size_t arraySize = 10;
    std::array<int, arraySize> arraySequence = generateAndSort<std::array<int, arraySize>, arraySize>(N);
    std::cout << "Initial sorted array sequence: ";
    for (const int& num : arraySequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // removeElementsByUserInput(arraySequence);

    return 0;
}