#include "./generalized_matrix.hpp"
#include "./chess_piece.hpp"

int main() {
    try {
        MATRIX::Matrix<int> matrix1(3, 3);
        MATRIX::Matrix<int> matrix2(3, 3);

        matrix1(0, 0) = 1;
        matrix1(1, 1) = 2;
        matrix1(2, 2) = 3;

        matrix2(0, 0) = 4;
        matrix2(1, 1) = 5;
        matrix2(2, 2) = 6;

        MATRIX::Matrix<int> matrix3 = matrix1 + matrix2;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                std::cout << matrix3(i, j) << " ";
            }
            std::cout << std::endl;
        }

        matrix1.move(0, 0, 2, 2);
        std::cout << "After move operation:" << std::endl;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                std::cout << matrix1(i, j) << " ";
            }
            std::cout << std::endl;
        }

        auto row = matrix1.row(1);
        std::cout << "Row 1:" << std::endl;
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        auto column = matrix1.column(2);
        std::cout << "Column 2:" << std::endl;
        for (const auto& val : column) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        MATRIX::Matrix<MATRIX::Chess_piece> chess_board(8, 8);
        chess_board(0, 0) = MATRIX::Chess_piece(MATRIX::Chess_piece::Type::Rook);
        chess_board(0, 1) = MATRIX::Chess_piece(MATRIX::Chess_piece::Type::Knight);

        chess_board.print();

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

// #include <iostream>
// #include "./matrix.hpp"

// int main() {
//     try {
//         MATRIX::Imatrix<int> matrix1(3, 3);
//         MATRIX::Imatrix<int> matrix2(3, 3);

//         matrix1(0, 0) = 1;
//         matrix1(1, 1) = 2;
//         matrix1(2, 2) = 3;

//         matrix2(0, 0) = 4;
//         matrix2(1, 1) = 5;
//         matrix2(2, 2) = 6;

//         MATRIX::Imatrix<int> matrix3 = matrix1 + matrix2;
//         for (size_t i = 0; i < 3; ++i) {
//             for (size_t j = 0; j < 3; ++j) {
//                 std::cout << matrix3(i, j) << " ";
//             }
//             std::cout << std::endl;
//         }

//         matrix1.move(0, 0, 2, 2);
//         std::cout << "After move operation:" << std::endl;
//         for (size_t i = 0; i < 3; ++i) {
//             for (size_t j = 0; j < 3; ++j) {
//                 std::cout << matrix1(i, j) << " ";
//             }
//             std::cout << std::endl;
//         }

//         auto row = matrix1.row(1);
//         std::cout << "Row 1:" << std::endl;
//         for (const auto& val : row) {
//             std::cout << val << " ";
//         }
//         std::cout << std::endl;

//         auto column = matrix1.column(2);
//         std::cout << "Column 2:" << std::endl;
//         for (const auto& val : column) {
//             std::cout << val << " ";
//         }
//         std::cout << std::endl;
//     }
//     catch (const std::exception& e) {
//         std::cerr << e.what() << std::endl;
//     }
//     return 0;
// }