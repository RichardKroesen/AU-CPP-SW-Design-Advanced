#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <array>
#include <set>
#include <unordered_set>
#include <algorithm>

#include "./container.hpp"
#include "./performance_measurer.hpp"

template <size_t count, int min = 1, int max = 100>
std::vector<MyStruct> generateDistinctRandomLargeStructs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    std::unordered_set<int> unique_nums;
    while (unique_nums.size() < count) {
        unique_nums.insert(dis(gen));
    }

    std::vector<MyStruct> unique_structs;
    for (const auto& num : unique_nums) {
        MyStruct ls;
        ls.value = num;
        std::fill(std::begin(ls.large_array), std::end(ls.large_array), num);
        unique_structs.push_back(ls);
    }

    return unique_structs;
}

int main() {
    const size_t N = 1000;
    auto random_large_structs = generateDistinctRandomLargeStructs<N, 1, N + 1>();

    // VECTOR
    std::vector<MyStruct> vec;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR", [&vec, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            vec.push_back(item);
            std::sort(vec.begin(), vec.end());
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR-DEL", [&vec, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
        }
    });

    std::cout << std::endl;

    // VECTOR_AL
    std::vector<MyStruct> vecAl;
    vecAl.reserve(N);
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL", [&vecAl, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            vecAl.push_back(item);
            std::sort(vecAl.begin(), vecAl.end());
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL-DEL", [&vecAl, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            vecAl.erase(std::remove(vecAl.begin(), vecAl.end(), item), vecAl.end());
        }
    });

    std::cout << std::endl;

    // LIST with pre-allocation
    std::list<MyStruct> lst(N); // Pre-allocate list with N elements
    auto it = lst.begin();
    for (const auto& item : random_large_structs) {
        *it = item;
        ++it;
    }
    lst.clear(); // Clear the list to start fresh

    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST", [&lst, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            lst.push_back(item);
            lst.sort();
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST-DEL", [&lst, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            lst.remove(item);
        }
    });

    std::cout << std::endl;

    // ARRAY
    std::array<MyStruct, N> arr;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY", [&arr, &random_large_structs]() {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = random_large_structs[i];
            std::sort(arr.begin(), arr.begin() + i + 1);
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY-DEL", [&arr, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            auto it = std::find(arr.begin(), arr.end(), item);
            if (it != arr.end()) {
                *it = MyStruct{0};  // Assuming 0 is a marker for removal
            }
        }
    });

    std::cout << std::endl;

    // SET
    std::set<MyStruct> st;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET", [&st, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            st.insert(item);
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET-DEL", [&st, &random_large_structs]() {
        for (const auto& item : random_large_structs) {
            st.erase(item);
        }
    });

    std::cout << std::endl;

    return 0;
}