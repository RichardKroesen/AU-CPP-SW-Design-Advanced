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
set(TEST1 Find_All_Test)
add_executable(${TEST1} 
    find_all_test.cc
)

target_link_libraries(${TEST1} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST1} COMMAND Find_All_Test)

# TEST 2 - Test the function
set(TEST2 Synch_Queue_Test)
add_executable(${TEST2} 
    synch_queue_test.cc
)

target_link_libraries(${TEST2} PRIVATE
    gtest_main
    gmock_main
)

add_test(NAME ${TEST2} COMMAND Synch_Queue_Test)

set_target_properties(gtest gtest_main gmock gmock_main
    PROPERTIES
    CXX_CLANG_TIDY ""
)