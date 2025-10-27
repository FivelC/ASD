// Copyright 2024 Marina Usova

#define MATRIX
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE
#ifdef MATRIX
#include <iostream>
#include "../lib_matrix/matrix.h"
#include "../lib_mathvector/mathvector.h"
#include "../lib_trianglematrix/trianglematrix.h"

template <typename T>
Matrix<T> matrixUserInput() {
    int row, column;

    std::cout << "Please, enter the size of matrix (row column): ";
    std::cin >> row;
    std::cin >> column;
    try {
        Matrix<T> baseMatrix(row, column);
        std::cout << "Input matrix: " << std::endl;
        std::cin >> baseMatrix;
        return baseMatrix;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

template <typename T>
TriangleMatrix<T> trianglematrixUserInput() {
    int row, column;

    std::cout << "Please, enter the size of matrix (row column): ";
    std::cin >> row;
    std::cin >> column;
    try {
        TriangleMatrix<T> trMatrix(row, column);
        std::cout << "Input matrix: " << std::endl;
        std::cin >> trMatrix;
        return trMatrix;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

template <typename T>
MathVector<T> vectorUserInput() {
    int size;

    std::cout << "Please, enter the size of vector: ";
    std::cin >> size;
    try {
        MathVector<T> vector(size);
        std::cout << "Input vector: " << std::endl;
        std::cin >> vector;
        return vector;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

void matrixOperations() {
    while (true) {
        system("cls");
        std::cout << "=== MATRIX OPERATIONS ===\n"
            << "1. Matrix * Matrix\n"
            << "2. Matrix * Vector\n"
            << "3. Vector * Matrix\n"
            << "4. Matrix + Matrix\n"
            << "5. Matrix - Matrix\n"
            << "0. Back to main menu" << std::endl;
        std::cout << "Please choose an action: ";
        int user_choice;
        std::cin >> user_choice;

        if (user_choice == 0) {
            break;
        }

        Matrix<int> matrix1;
        Matrix<int> matrix2;
        Matrix<int> matrix3;
        MathVector<int> vector1;
        MathVector<int> vector2;

        switch (user_choice) {
        case 1:
            system("cls");
            try {
                matrix1 = matrixUserInput<int>();
                matrix2 = matrixUserInput<int>();
                matrix3 = matrix1 * matrix2;
                std::cout << "Answer:\n" << matrix3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 2:
            system("cls");
            try {
                matrix1 = matrixUserInput<int>();
                vector1 = vectorUserInput<int>();
                vector2 = matrix1 * vector1;
                std::cout << "Answer:\n" << vector2;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 3:
            system("cls");
            try {
                vector1 = vectorUserInput<int>();
                matrix1 = matrixUserInput<int>();
                vector2 = vector1 * matrix1;
                std::cout << "Answer:\n" << vector2;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 4:
            system("cls");
            try {
                matrix1 = matrixUserInput<int>();
                matrix2 = matrixUserInput<int>();
                matrix3 = matrix1 + matrix2;
                std::cout << "Answer:\n" << matrix3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 5:
            system("cls");
            try {
                matrix1 = matrixUserInput<int>();
                matrix2 = matrixUserInput<int>();
                matrix3 = matrix1 - matrix2;
                std::cout << "Answer:\n" << matrix3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        default:
            std::cout << "Wrong Input. Try again!" << std::endl;
            system("pause");
            break;
        }
    }
}

void triangleMatrixOperations() {
    while (true) {
        system("cls");
        std::cout << "=== TRIANGLE MATRIX OPERATIONS ===\n"
            << "1. TriangleMatrix * TriangleMatrix\n"
            << "2. TriangleMatrix + TriangleMatrix\n"
            << "3. TriangleMatrix - TriangleMatrix\n"
            << "0. Back to main menu" << std::endl;
        std::cout << "Please choose an action: ";
        int user_choice;
        std::cin >> user_choice;

        if (user_choice == 0) {
            break;
        }

        TriangleMatrix<int> tr_matrix_1;
        TriangleMatrix<int> tr_matrix_2;
        TriangleMatrix<int> tr_matrix_3;

        switch (user_choice) {
        case 1:
            system("cls");
            try {
                tr_matrix_1 = trianglematrixUserInput<int>();
                tr_matrix_2 = trianglematrixUserInput<int>();
                tr_matrix_3 = tr_matrix_1 * tr_matrix_2;
                std::cout << "Answer:\n" << tr_matrix_3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 2:
            system("cls");
            try {
                tr_matrix_1 = trianglematrixUserInput<int>();
                tr_matrix_2 = trianglematrixUserInput<int>();
                tr_matrix_3 = tr_matrix_1 + tr_matrix_2;
                std::cout << "Answer:\n" << tr_matrix_3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        case 3:
            system("cls");
            try {
                tr_matrix_1 = trianglematrixUserInput<int>();
                tr_matrix_2 = trianglematrixUserInput<int>();
                tr_matrix_3 = tr_matrix_1 - tr_matrix_2;
                std::cout << "Answer:\n" << tr_matrix_3;
                system("pause");
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                system("pause");
            }
            break;
        default:
            std::cout << "Wrong Input. Try again!" << std::endl;
            system("pause");
            break;
        }
    }
}


void main() {
    while (true) {
        system("cls");
        std::cout << "=== MAIN MENU ===\n"
            << "1. Regular Matrix Operations\n"
            << "2. Triangle Matrix Operations\n"
            << "0. Exit" << std::endl;
        std::cout << "Please choose matrix type: ";
        int user_choice;
        std::cin >> user_choice;

        if (user_choice == 0) {
            break;
        }

        switch (user_choice) {
        case 1:
            matrixOperations();
            break;
        case 2:
            triangleMatrixOperations();
            break;
        default:
            std::cout << "Wrong Input. Try again!" << std::endl;
            system("pause");
            break;
        }
    }
}
#endif // MATRIX
