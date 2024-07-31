#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <type_traits>
#include <concepts>
#include <iostream>

namespace MEMORY
{

// Concept for containers that store integers
template<typename T>
concept SortableIntContainer = requires(T container) {
    typename T::value_type;
    requires std::is_same_v<typename T::value_type, int>;
    { container.begin() } -> std::same_as<typename T::iterator>;
    { container.end() } -> std::same_as<typename T::iterator>;
    { container.size() } -> std::convertible_to<size_t>;
};

template <SortableIntContainer Container>
void print(Container& sequence) {
    std::cout << "Container: ";
    for (const auto& num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

template <SortableIntContainer Container>
void sort(Container& sequence) {

    if constexpr (std::is_same_v<Container, std::set<int>>) {
        return;
    }

    // Sort
    if constexpr (std::is_same_v<Container, std::list<int>>) {
        sequence.sort();
    } else if constexpr (requires { std::sort(sequence.begin(), sequence.end()); }) {
        std::sort(sequence.begin(), sequence.end());
    } else {
        static_assert(false, "Container type does not support sorting");
    }
}

template <SortableIntContainer Container>
void removeAllElements(Container& sequence) {
    if constexpr (std::is_same_v<Container, std::vector<int>> || 
                  std::is_same_v<Container, std::list<int>> ||
                  std::is_same_v<Container, std::set<int>>) {
        sequence.clear();
    } else if constexpr (std::is_array_v<Container>) {
        std::fill(sequence.begin(), sequence.end(), 0);
    }
}

} // namespace MEMORY
#endif // CONTAINER_HPP