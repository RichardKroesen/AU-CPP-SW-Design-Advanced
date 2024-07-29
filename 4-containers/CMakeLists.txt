cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(CONTAINERS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# On My System I have to set the compiler path: 
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Enable clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
else()
  message(WARNING "clang-tidy not found.")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(CONTAINERS src/main.cpp)

set_target_properties(CONTAINERS PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
add_subdirectory(tests)