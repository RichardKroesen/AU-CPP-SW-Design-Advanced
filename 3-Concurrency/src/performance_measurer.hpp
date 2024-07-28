#ifndef PERFORMANCE_MEASURER_HPP
#define PERFORMANCE_MEASURER_HPP

#include <chrono>
#include <iostream>
#include <string>

namespace BENCHMARK_TOOL
{

class PerformanceMeasurer {
public:
    template <typename Func>
    static void measure(const std::string& description, Func&& func) {
        auto start = std::chrono::high_resolution_clock::now();
        
        func();
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << description << " took " << duration.count() << " ms" << std::endl;
    }
}; // class Performance
} // namespace BENCHMARK_TOOL
#endif // PERFORMANCE_MEASURER_HPP