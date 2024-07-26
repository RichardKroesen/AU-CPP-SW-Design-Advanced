#include <gtest/gtest.h>
#include <chrono>
#include <random>

#include "../src/object_searcher.hpp" // CUD

std::vector<int> generateRandomVector(size_t size, const int min, const int max, unsigned int seed) {
    std::vector<int> vec(size);
    std::mt19937 rng(seed); // Mersenne Twister pseudo-random generator, source: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/ 
    std::uniform_int_distribution<int> dist(min, max);

    for (auto& el : vec) {
        el = dist(rng);
    }

    return vec;
}

TEST(find_all_Test, Test1) {
    std::vector<int> numbers = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10};
    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll<10>(8);
    std::vector<int> expected = {8, 8};
    
    for (int i = 0; i < results.size(); ++i) {
        EXPECT_EQ(*results[i], expected[i]);
    }
}

TEST(find_all_Test, Test2) {
    std::vector<int> numbers = {1, 2, 2, 2, 5, 8, 7, 2, 8, 10};

    SEARCHER::Finder<int> finder(numbers);
    std::vector<int*> results = finder.findAll<1>(8);
    std::vector<int> expected = {8, 8};
    
    for (int i = 0; i < results.size(); ++i) {
        EXPECT_EQ(*results[i], expected[i]);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}