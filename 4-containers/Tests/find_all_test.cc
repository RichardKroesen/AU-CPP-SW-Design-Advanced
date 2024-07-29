#include <gtest/gtest.h>
#include <chrono>
#include <random>
#include <algorithm>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}