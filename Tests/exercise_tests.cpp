#include <gtest/gtest.h>
#include <chrono>

#include "../linear_search.hpp" // Code under test (CUD)


TEST(LinearSearchTest, FindSevenInMiddle) {
    std::vector<int> intArr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int actual_position = 6;

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 7), actual_position);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindSevenInMiddle took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, NoSevenInVector) {
    std::vector<int> intArr = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11};

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 7), -1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "NoSevenInVector took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, FindElementLessThanSevenInMiddle) {
    std::vector<int> intArr = {8, 9, 10, 5, 11, 12, 13};

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 5), 3);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FindElementLessThanSevenInMiddle took " << elapsed.count() << " seconds." << std::endl;
}

TEST(LinearSearchTest, NoElementLessThanSevenInVector) {
    std::vector<int> intArr = {8, 9, 10, 11, 12, 13, 14};

    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(linearSearch(intArr, 5), -1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "NoElementLessThanSevenInVector took " << elapsed.count() << " seconds." << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}