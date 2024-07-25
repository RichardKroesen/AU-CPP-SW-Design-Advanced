cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(MICRO_BENCH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# On My System I have to set the compiler path: 
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(MICRO_BENCH main.cpp)

add_subdirectory(tests)