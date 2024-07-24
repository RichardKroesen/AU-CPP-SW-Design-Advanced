#include <gtest/gtest.h>
#include "../linear_search.hpp"

TEST(LinearSearchTest, FindSevenInMiddle) {
    std::vector<int> intArr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int actual_position = 6;

    EXPECT_EQ(linearSearch(intArr, 7), actual_position);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}