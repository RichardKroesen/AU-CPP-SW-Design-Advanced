#ifndef GENERALIZED_MATRIX_HPP
#define GENERALIZED_MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <concepts>
#include <type_traits>

namespace MATRIX {

template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
};

template <typename T>
concept Modulo = requires(T a, T b) {
    { a % b } -> std::same_as<T>;
};

template <typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{})) {}

    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) noexcept = default;

    T& operator()(size_t x, size_t y) {
        check_bounds(x, y);
        return data[x][y];
    }

    const T& operator()(size_t x, size_t y) const {
        check_bounds(x, y);
        return data[x][y];
    }

    template <Arithmetic U>
    Matrix operator+(const Matrix<U>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator+(const T& scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + scalar;
            }
        }
        return result;
    }

    template <Arithmetic U>
    Matrix operator-(const Matrix<U>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const T& scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] - scalar;
            }
        }
        return result;
    }

    template <Arithmetic U>
    Matrix operator*(const Matrix<U>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] * other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const T& scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

    template <Arithmetic U>
    Matrix operator/(const Matrix<U>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator/(const T& scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] / scalar;
            }
        }
        return result;
    }

    template <Modulo U>
    Matrix operator%(const Matrix<U>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] % other.data[i][j];
            }
        }
        return result;
    }

    template <Modulo U>
    Matrix operator%(const U& scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] % scalar;
            }
        }
        return result;
    }

    void move(size_t from_x, size_t from_y, size_t to_x, size_t to_y) {
        check_bounds(from_x, from_y);
        check_bounds(to_x, to_y);
        data[to_x][to_y] = data[from_x][from_y];
        data[from_x][from_y] = T{};
    }

    std::vector<T> row(size_t n) const {
        if (n >= rows) {
            throw std::out_of_range("Row index out of range");
        }
        return data[n];
    }

    std::vector<T> column(size_t n) const {
        if (n >= cols) {
            throw std::out_of_range("Column index out of range");
        }
        std::vector<T> col(rows);
        for (size_t i = 0; i < rows; ++i) {
            col[i] = data[i][n];
        }
        return col;
    }
    
    void print() const {
        for (const auto& row : data) {
            for (const auto& element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    size_t rows, cols;
    std::vector<std::vector<T>> data;

    void check_bounds(size_t x, size_t y) const {
        if (x >= rows || y >= cols) {
            throw std::out_of_range("Index out of range");
        }
    }
}; // class Matrix
} // namespace MATRIX 
#endif // GENERALIZED_MATRIX_HPP