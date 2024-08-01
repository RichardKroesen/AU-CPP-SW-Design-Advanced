#include <iostream>
#include <unordered_set>
#include <random>
#include <unordered_set>
#include <set>

#include "./container.hpp"
#include "./performance_measurer.hpp"

template <size_t count, int min = 1, int max = 100>
std::vector<int> generateDistinctRandomInts() {
    static_assert(!(count > static_cast<size_t>(max - min + 1)), "Only integer types are supported");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    std::unordered_set<int> unique_nums;
    while (unique_nums.size() < count) {
        unique_nums.insert(dis(gen));
    }

    return std::vector<int>(unique_nums.begin(), unique_nums.end());
}


int main() {
    const size_t N = 100;
    auto random_structs = generateDistinctRandomStructs<N, 1, N + 1>();

    // VECTOR
    std::vector<MyStruct> vec;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR", [&vec, &random_structs]() {
        for (const auto& item : random_structs) {
            vec.push_back(item);
            std::sort(vec.begin(), vec.end());
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR-DEL", [&vec, &random_structs]() {
        for (const auto& item : random_structs) {
            vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
        }
    });

    std::cout << std::endl;

    // VECTOR_AL
    std::vector<MyStruct> vecAl;
    vecAl.reserve(N);
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL", [&vecAl, &random_structs]() {
        for (const auto& item : random_structs) {
            vecAl.push_back(item);
            std::sort(vecAl.begin(), vecAl.end());
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL-DEL", [&vecAl, &random_structs]() {
        for (const auto& item : random_structs) {
            vecAl.erase(std::remove(vecAl.begin(), vecAl.end(), item), vecAl.end());
        }
    });

    std::cout << std::endl;

    // LIST
    std::list<MyStruct> lst;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST", [&lst, &random_structs]() {
        for (const auto& item : random_structs) {
            lst.push_back(item);
            lst.sort();
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST-DEL", [&lst, &random_structs]() {
        for (const auto& item : random_structs) {
            lst.remove(item);
        }
    });

    std::cout << std::endl;

    // ARRAY
    std::array<MyStruct, N> arr;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY", [&arr, &random_structs]() {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = random_structs[i];
            std::sort(arr.begin(), arr.begin() + i + 1);
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY-DEL", [&arr, &random_structs]() {
        for (const auto& item : random_structs) {
            auto it = std::find(arr.begin(), arr.end(), item);
            if (it != arr.end()) {
                *it = MyStruct{0};  // Assuming 0 is a marker for removal
            }
        }
    });

    std::cout << std::endl;

    // SET
    std::set<MyStruct> st;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET", [&st, &random_structs]() {
        for (const auto& item : random_structs) {
            st.insert(item);
        }
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET-DEL", [&st, &random_structs]() {
        for (const auto& item : random_structs) {
            st.erase(item);
        }
    });

    std::cout << std::endl;

    return 0;
}