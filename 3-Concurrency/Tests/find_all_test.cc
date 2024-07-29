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

std::string generateRandomString(size_t length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, characters.size() - 1);
    std::string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[dist(rng)];
    }
    return random_string;
}

template <size_t threadsCount>
void runStringPerformanceTest(size_t vectorSize, const std::string& searchString) {
    std::vector<std::string> strings;
    strings.reserve(vectorSize);

    // Generate random strings
    for (size_t i = 0; i < vectorSize - 1; ++i) {
        strings.push_back(generateRandomString(10));  // 10-character strings
    }
    strings.push_back(searchString);  // Add the search string to ensure it exists

    SEARCHER::Finder<std::string> finder(strings);

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Single-threaded string search", [&]() {
        auto results = finder.single_findAll(searchString);
        EXPECT_GT(results.size(), 0);
    });

    std::string multiThreadedDescription = "Multi-threaded string search (" + std::to_string(threadsCount) + " threads)";
    BENCHMARK_TOOL::PerformanceMeasurer::measure(multiThreadedDescription, [&]() {
        auto results = finder.findAll<threadsCount>(searchString);  // Using default parameter here
        EXPECT_GT(results.size(), 0);
    });
}

TEST(find_all_ValueTest, EmptyVector) {
    std::vector<int> numbers;
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.single_findAll(5);
    EXPECT_TRUE(results.empty());
}

TEST(find_all_ValueTest, SingleElement_Found) {
    std::vector<int> numbers = {5};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.single_findAll(5);
    
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(*results[0], 5);
}

TEST(find_all_ValueTest, SingleElement_NotFound) {
    std::vector<int> numbers = {5};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.single_findAll(10);
    
    EXPECT_TRUE(results.empty());
}

TEST(find_all_ValueTest, MultipleElements_AllSame) {
    std::vector<int> numbers(10, 5);  // Vector of 10 elements, all 5
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll(5);
    
    ASSERT_EQ(results.size(), 10);
    for (const auto& result : results) {
        EXPECT_EQ(*result, 5);
    }
}

TEST(find_all_ValueTest, MultipleElements_SomeFound) {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2, 6};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll(2);
    
    ASSERT_EQ(results.size(), 4);
    for (const auto& result : results) {
        EXPECT_EQ(*result, 2);
    }
}

TEST(find_all_ValueTest, MultipleElements_NoneFound) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll(11);
    
    EXPECT_TRUE(results.empty());
}

TEST(find_all_ValueTest, LargeVector) {
    std::vector<int> numbers = generateRandomVector(1000000, 1, 1000, 42);
    int searchValue = 500;  // A value likely to appear multiple times
    
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll(searchValue);
    
    EXPECT_FALSE(results.empty());
    for (const auto& result : results) {
        EXPECT_EQ(*result, searchValue);
    }
}

TEST(find_all_ValueTest, FirstAndLastElements) {
    std::vector<int> numbers = {5, 2, 3, 4, 1, 6, 7, 8, 9, 5};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll(5);
    
    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(*results[0], numbers[0]);
    EXPECT_EQ(*results[1], numbers[9]);
}

TEST(find_all_ValueTest, CompareMultiThreaded) {
    std::vector<int> numbers = generateRandomVector(1000000, 1, 1000, 42);
    int searchValue = 500;
    
    SEARCHER::Finder<int> finder(numbers);
    
    std::vector<int*> singleThreadResults = finder.findAll(searchValue);
    std::vector<int*> multiThreadResults = finder.findAll<4>(searchValue);
    
    ASSERT_EQ(singleThreadResults.size(), multiThreadResults.size());
    
    std::sort(singleThreadResults.begin(), singleThreadResults.end());
    std::sort(multiThreadResults.begin(), multiThreadResults.end());
    
    for (size_t i = 0; i < singleThreadResults.size(); ++i) {
        EXPECT_EQ(singleThreadResults[i], multiThreadResults[i]);
    }
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

#define SEARCHER_TEST_SIZE 1000000
TEST(find_all_Performance, SmallDataset) {
    std::vector<int> numbers = generateRandomVector(SEARCHER_TEST_SIZE+1, 1, 1000, 42);
    numbers.push_back(500);  // Add a guaranteed element to the end

    SEARCHER::Finder<int> finder(numbers);
    int searchKey = 500;  // Guaranteed to exist

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Single-threaded search (small dataset)", [&]() {
        auto results = finder.single_findAll(searchKey);
        EXPECT_GT(results.size(), 0);
    });

    BENCHMARK_TOOL::PerformanceMeasurer::measure("Multi-threaded search (small dataset, 4 threads)", [&]() {
        auto results = finder.findAll<20>(searchKey);
        EXPECT_GT(results.size(), 0);
    });
}

TEST(find_all_Performance, LargeStringDataset) {
    runStringPerformanceTest<10>(SEARCHER_TEST_SIZE, "TESTSEARCH");
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
    std::vector<int> numbers = generateRandomVector(10'000'000, 1, 1'000'000, 42);
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