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
set(TEST1 find_seven_test)
add_executable(${TEST1} 
    exercise_tests.cpp
)

target_link_libraries(${TEST1} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST1} COMMAND find_seven_test)

# TEST 2 - Measure the Performance
set(TEST2 performance_test)
add_executable(${TEST2} 
    performance_test.cpp
)

target_link_libraries(${TEST2} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST2} COMMAND performance_test)