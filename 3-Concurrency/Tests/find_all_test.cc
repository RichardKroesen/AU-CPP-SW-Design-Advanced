#include <gtest/gtest.h>
#include <chrono>
#include <random>
#include <algorithm>

#include "../src/object_searcher.hpp"
#include "../src/performance_measurer.hpp"

std::vector<int> generateRandomVector(size_t size, const int min, const int max, unsigned int seed) {
    std::vector<int> vec(size);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);

    for (auto& el : vec) {
        el = dist(rng);
    }

    return vec;
}

TEST(find_all_Test, Test1) {
    std::vector<int> numbers = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.single_findAll(8);
    std::vector<int> expected = {8, 8};
    
    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i) {
        EXPECT_EQ(*results[i], expected[i]);
    }
}

TEST(find_all_Test, Test2) {
    std::vector<int> numbers = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10};

    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.single_findAll(8);
    std::vector<int> expected = {8, 8};
    
    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i) {
        EXPECT_EQ(*results[i], expected[i]);
    }
}

TEST(find_all_Performance, SmallDataset) {
    std::vector<int> numbers = generateRandomVector(1000, 1, 1000, 42);
    SEARCHER::Finder<int> finder(numbers);
    int searchKey = numbers[500];  // Guaranteed to exist

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Single-threaded search (small dataset)", [&]() {
        auto results = finder.single_findAll(searchKey);
        EXPECT_GT(results.size(), 0);
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Multi-threaded search (small dataset, 4 threads)", [&]() {
        auto results = finder.findAll<10>(searchKey);
        EXPECT_GT(results.size(), 0);
    });
}

TEST(find_all_Performance, LargeDataset) {
    std::vector<int> numbers = generateRandomVector(10000000, 1, 1000000, 42);
    SEARCHER::Finder<int> finder(numbers);
    int searchKey = numbers[5000000];  // Guaranteed to exist

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Single-threaded search (large dataset)", [&]() {
        auto results = finder.single_findAll(searchKey);
        EXPECT_GT(results.size(), 0);
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Multi-threaded search (large dataset, 4 threads)", [&]() {
        auto results = finder.findAll<10>(searchKey);
        EXPECT_GT(results.size(), 0);
    });
}

TEST(find_all_Performance, CompareThreadCounts) {
    std::vector<int> numbers = generateRandomVector(10000000, 1, 1000000, 42);
    SEARCHER::Finder<int> finder(numbers);
    int searchKey = numbers[5000000];  // Guaranteed to exist

    std::vector<size_t> threadCounts = {1, 2, 4, 8, 16};
    
    for (size_t threads : threadCounts) {
        std::string description = "Multi-threaded search (large dataset, " + std::to_string(threads) + " threads)";
        BENCHMARK_TOOL::PerformanceMeasurer::measure(description, [&]() {
            switch (threads) {
                case 1:
                    finder.single_findAll(searchKey);
                    break;
                case 2:
                    finder.findAll<2>(searchKey);
                    break;
                case 4:
                    finder.findAll<4>(searchKey);
                    break;
                case 8:
                    finder.findAll<8>(searchKey);
                    break;
                case 16:
                    finder.findAll<16>(searchKey);
                    break;
            }
        });
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}