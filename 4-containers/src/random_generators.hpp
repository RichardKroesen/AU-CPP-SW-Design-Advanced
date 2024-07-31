#ifndef RANDOM_GENERATORS_HPP
#define RANDOM_GENERATORS_HPP

#include <vector>
#include <random>

namespace BENCHMARK_TOOL
{

template <typename Container, size_t N = 0> 
auto generate(size_t N_runtime) {
    Container sequence;
    size_t size = (N > 0) ? N : N_runtime;

    // Generate Random Integers
    for (size_t i = 0; i < size; ++i) {
        auto element = std::rand() % 100;
        if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::list<int>>) {
            sequence.push_back(element);
        } else if constexpr (std::is_same_v<Container, std::array<int, N>>) {
            if (i < N_runtime) {
                sequence[i] = element;
            } else {
                sequence[i] = 0;
            }
        }
    }
    return sequence;
}
    
std::vector<int> generateRandomVector(size_t size, const int min, const int max, unsigned int seed) {
    std::vector<int> vec(size);
    std::mt19937 rng(seed); // Mersenne Twister pseudo-random generator, source: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/ 
    std::uniform_int_distribution<int> dist(min, max);

    for (auto& el : vec) {
        el = dist(rng);
    }

    return vec;
}

} // namespace BENCHMARK_TOOL
#endif // RANDOM_GENERATORS_HPP