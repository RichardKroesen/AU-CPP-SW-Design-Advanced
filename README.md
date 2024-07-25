# AU-CPP-SW-Design-Advanced

This is my repository of the exercises during the Aarhus Summer School 2024 modern C++ Software Design from Bjarne Stroustrup, in Denemark.

In this course the scope is on the 2 : 1 on the why of software design using modern C++, and here and there some hands-on like the linear search exercise.

## Project Configuration

*I put every exercise in a seperate folder, here is the description for the first complete C++ exercise of MicroBenchmark:*

To set up the project, you will need CMake and a C++20 compatible compiler (such as GCC or Clang).
I used GCC13.2.0 with MinGW, because I already had on my machine and have experience using it on Embedded Single-Board-Computers.

### Steps to Configure and Build the Project

1. **Clone the Repository**:

    ```sh
    git clone https://github.com/your-username/AU-CPP-SW-Design-Advanced.git
    cd AU-CPP-SW-Design-Advanced
    ```

2. **Create a Build Directory**:

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake to Generate Build Files**:

    ```sh
    cmake -S .. -B . -DCMAKE_C_COMPILER="C:/MinGW/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe"
    ```

4. **Build the Project**:

    ```sh
    cmake --build .
    ```

Personally I use VScode with CMake plug-in, so I don't have to use the command line interface for compiling everytime.

## Unit Tests

This project uses Google Test for unit testing. The tests are located in the `tests` directory.

### Running Unit Tests

To run the unit tests, follow these steps:

1. **Navigate to the Build Directory** (if not already there):

    ```sh
    cd build
    ```

2. **Run the Tests**:

    ```sh
    ./Tests/[TEST_NAME]
    ```

### Test Cases

The current test cases include:

1. **Find a 7 in the Middle of a Vector**:
    - Generates a large vector of random integers and places the number 7 in the middle.
    - Measures the time taken to find the number 7.

2. **No 7 in the Vector**:
    - Generates a large vector of random integers without the number 7.
    - Measures the time taken to confirm that 7 is not in the vector.

3. **Find an Element Less Than 7 in the Middle of a Vector**:
    - Generates a large vector of random integers and places a number less than 7 in the middle.
    - Measures the time taken to find the number less than 7.

4. **No Element Less Than 7 in the Vector**:
    - Generates a large vector of random integers where all elements are greater than or equal to 7.
    - Measures the time taken to confirm that no element less than 7 is in the vector.

5. **Find a Specific String in a Vector of Random Strings**:
    - Generates a large vector of random 20-letter strings and searches for a specific string that doesn't exist.
    - Measures the time taken to confirm that the string is not in the vector.

6. **Find a Specific String Placed in the Middle of a Vector of Random Strings**:
    - Generates a large vector of random 20-letter strings and places a specific string in the middle.
    - Measures the time taken to find the specific string.

### Example Output

When running the tests, you should see output similar to the following, indicating the time taken for each test:

```bash
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from LinearSearchTest
[ RUN      ] LinearSearchTest.FindSevenInMiddle
FindSevenInMiddle took 0.0189305 seconds.
[       OK ] LinearSearchTest.FindSevenInMiddle (325 ms)
[ RUN      ] LinearSearchTest.NoSevenInVector
NoSevenInVector took 0.038035 seconds.
[       OK ] LinearSearchTest.NoSevenInVector (342 ms)
[ RUN      ] LinearSearchTest.FindElementLessThanSevenInMiddle
FindElementLessThanSevenInMiddle took 0.0196483 seconds.
[       OK ] LinearSearchTest.FindElementLessThanSevenInMiddle (321 ms)
[ RUN      ] LinearSearchTest.NoElementLessThanSevenInVector
NoElementLessThanSevenInVector took 0.0401622 seconds.
[       OK ] LinearSearchTest.NoElementLessThanSevenInVector (351 ms)
[----------] 4 tests from LinearSearchTest (1380 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (1400 ms total)
[  PASSED  ] 4 tests.
```
