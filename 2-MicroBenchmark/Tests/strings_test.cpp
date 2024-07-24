#include <gtest/gtest.h>
#include <chrono>
#include <random>

#include "../linear_search.hpp"

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

std::vector<std::string> generateRandomStringVector(size_t size, size_t string_length, unsigned int seed) {
    std::vector<std::string> vec(size);
    std::mt19937 rng(seed);

    for (auto& el : vec) {
        el = generateRandomString(string_length);
    }

    return vec;
}

TEST(LinearSearchTest, FindTwentyXsInVector) {
    std::vector<std::string> stringArr = generateRandomStringVector(1000000, 20, 999); 

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(stringArr, std::string(20, 'X')), -1); // Very unlikely to find 20 Xs in the vector
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindTwentyXsInVector took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, FindTwentyXsInMiddle) {
    std::vector<std::string> stringArr = generateRandomStringVector(1000000, 20, 999);
    stringArr[500000] = std::string(20, 'X'); // Place "XXXXXXXXXXXXXXXXXXXX" in the middle

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(stringArr, std::string(20, 'X')), 500000);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindTwentyXsInMiddle took " << elapsed.count() << " seconds." << std::endl;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}