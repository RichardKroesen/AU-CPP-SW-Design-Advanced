#include <gtest/gtest.h>
#include "../linear_search.hpp"

TEST(LinearSearchTest, FindSevenInMiddle) {
    std::vector<int> intArr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int actual_position = 6;

    EXPECT_EQ(linearSearch(intArr, 7), actual_position);
}

TEST(LinearSearchTest, NoSevenInVector) {
    std::vector<int> intArr = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11};
    EXPECT_EQ(linearSearch(intArr, 7), -1);
}

TEST(LinearSearchTest, FindElementLessThanSevenInMiddle) {
    std::vector<int> intArr = {8, 9, 10, 5, 11, 12, 13};
    EXPECT_EQ(linearSearch(intArr, 5), 3);
}

TEST(LinearSearchTest, NoElementLessThanSevenInVector) {
    std::vector<int> intArr = {8, 9, 10, 11, 12, 13, 14};
    EXPECT_EQ(linearSearch(intArr, 5), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}