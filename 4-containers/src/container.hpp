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
#include <unordered_set>
#include <string>

struct MyStruct {
    int value;
    int large_array[100]; 

    bool operator<(const MyStruct& other) const {
        return value < other.value;
    }

    bool operator==(const MyStruct& other) const {
        return value == other.value;
    }
};

namespace MEMORY
{

// Concept for containers that store integers
template<typename T>
concept SortableContainer = requires(T container) {
    typename T::value_type;
    requires std::is_same_v<typename T::value_type, int> || 
             std::is_same_v<typename T::value_type, MyStruct>;
    { container.begin() } -> std::same_as<typename T::iterator>;
    { container.end() } -> std::same_as<typename T::iterator>;
    { container.size() } -> std::convertible_to<size_t>;
    requires requires(typename T::value_type a, typename T::value_type b) {
        { a < b } -> std::convertible_to<bool>;
    };
};

template <SortableContainer Container>
void print(Container& sequence) {
    std::cout << "Container: ";
    for (const auto& num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

template <SortableContainer Container>
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

template <SortableContainer Container>
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