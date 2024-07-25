cmake_minimum_required(VERSION 3.18)

include(CTest)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

# TEST 1 - Test the function
set(TEST1 Numbers_Test)
add_executable(${TEST1} 
    numbers_tests.cpp
)

target_link_libraries(${TEST1} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST1} COMMAND Numbers_Test)

# TEST 2 - Measure the Performance
set(TEST2 Strings_Test)
add_executable(${TEST2} 
    strings_test.cpp
)

target_link_libraries(${TEST2} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST2} COMMAND Strings_Test)