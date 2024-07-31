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
    auto random_nums = generateDistinctRandomInts<N, 1, N+1>();

    std::vector<int> vec; 
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR", [&vec, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            vec.push_back(random_nums[i]);
            MEMORY::sort(vec);
            // MEMORY::print(vec);
        }
    });
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR-DEL", [&vec, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            vec.erase(std::remove(vec.begin(), vec.end(), random_nums[i]), vec.end());
        }
    });
    // MEMORY::print(vec);
    std::cout << std::endl;

    std::vector<int> vecAl; 
    vecAl.reserve(N);
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL", [&vecAl, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            vecAl.push_back(random_nums[i]);
            MEMORY::sort(vecAl);
            // MEMORY::print(vecAl);
        }
    });
    BENCHMARK_TOOL::PerformanceMeasurer::measure("VECTOR_AL-DEL", [&vecAl, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            vecAl.erase(std::remove(vecAl.begin(), vecAl.end(), random_nums[i]), vecAl.end());
        }
    });
    // MEMORY::print(vecAl);
    std::cout << std::endl;

    std::list<int> lst;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST", [&lst, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            lst.push_back(random_nums[i]);
            MEMORY::sort(lst);
            // MEMORY::print(lst);
        }
    });
    BENCHMARK_TOOL::PerformanceMeasurer::measure("LIST-DEL", [&lst, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            lst.remove(random_nums[i]);
        }
    });
    // MEMORY::print(lst);
    std::cout << std::endl;

    std::array<int, N> arr;
    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY", [&arr, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = random_nums[i];
            MEMORY::sort(arr);
        }
    });
    BENCHMARK_TOOL::PerformanceMeasurer::measure("ARRAY-DEL", [&arr, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            arr[random_nums[i]] = 0;
        }
    }); 
    std::cout << std::endl;

    std::set<int> st;    
    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET", [&st, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            st.insert(random_nums[i]);
        }
    });
    BENCHMARK_TOOL::PerformanceMeasurer::measure("SET-DEL", [&st, &random_nums]() {
        for (size_t i = 0; i < N; ++i) {
            st.erase(random_nums[i]);
        }
    });
    std::cout << std::endl;
    return 0;
}