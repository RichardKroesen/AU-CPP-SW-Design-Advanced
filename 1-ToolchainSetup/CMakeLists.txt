cmake_minimum_required(VERSION 3.10)

project(TOOLCHAIN_EXERCISE VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

add_executable(TOOLCHAIN_EXERCISE main.cpp)