#include <gtest/gtest.h>
#include <chrono>
#include <random>

#include "../linear_search.hpp" // Code under test (CUD)

std::vector<int> generateRandomVector(size_t size, const int min, const int max, unsigned int seed) {
    std::vector<int> vec(size);
    std::mt19937 rng(seed); // Mersenne Twister pseudo-random generator, source: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/ 
    std::uniform_int_distribution<int> dist(min, max);

    for (auto& el : vec) {
        el = dist(rng);
    }

    return vec;
}

TEST(LinearSearchTest, FindSevenInMiddle) {
    // Data Arrange
    std::vector<int> intArr = generateRandomVector(10'000'000, 10, 20, 999);
    constexpr int actual_position = 5'000'000;

    // Act
    intArr[5'000'000] = 7;

    // Check
    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 7), actual_position);
    auto end = std::chrono::high_resolution_clock::now();

    // Results Printing
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindSevenInMiddle took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, NoSevenInVector) {
    std::vector<int> intArr = generateRandomVector(10'000'000, 10, 20, 999);
    constexpr int actual_position = -1;

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 7), actual_position);
    auto end = std::chrono::high_resolution_clock::now();

    // Results Printing
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "NoSevenInVector took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, FindElementLessThanSevenInMiddle) {
    std::vector<int> intArr = generateRandomVector(10'000'000, 10, 20, 999); 
    constexpr int actual_position = 5'000'000;

    intArr[5'000'000] = 5; // Set the middle element to 5

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 5), actual_position);
    auto end = std::chrono::high_resolution_clock::now();

    // Results Printing
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindElementLessThanSevenInMiddle took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, NoElementLessThanSevenInVector) {
    std::vector<int> intArr = generateRandomVector(10000000, 10, 20, 999);

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 5), -1);
    auto end = std::chrono::high_resolution_clock::now();

    // Results Printing
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "NoElementLessThanSevenInVector took " << elapsed.count() << " seconds." << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}