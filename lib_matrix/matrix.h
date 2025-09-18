

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>

#include "../lib_mathvector/mathvector.h"

template <typename T>
class Matrix : public MathVector<MathVector<T>> {
private:
    size_t _m;
    size_t _n;

public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    Matrix(const MathVector<MathVector<T>>&);
    Matrix(const Matrix&);

    Matrix<T> operator+(const Matrix& other);
    Matrix<T> operator-(const Matrix& other);

    Matrix<T> operator*(const T val);
    MathVector<T> operator*(const MathVector<T>& vec);

    friend MathVector<T> operator*(const MathVector<T>& vec,
        const Matrix<T>& matrix) {
        return MathVector<T>();
    }

    Matrix<T> operator*(const Matrix<T>& matr);

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& data) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Matrix<T>& data) {
        return is;
    }

private:
};

template <typename T>
Matrix<T>::Matrix(size_t m, size_t n) : _m(m), _n(n) {}

template <typename T>
Matrix<T>::Matrix() : _m(0), _n(0) {
    ;
}

template <typename T>
Matrix<T>::~Matrix() {
    ;
}

template <typename T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>&) {
    ;
}

template <typename T>
Matrix<T>::Matrix(const Matrix&) {
    ;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) {
    // return this->operator+(other);
    return Matrix<T>();
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) {
    return Matrix<T>();
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T val) {
    // Matrix<T> result();
    // for (int i = 0; i < _size; i++) {
    //   result[i] = (*this)[i] * val;
    // }
    // return result;
    return Matrix<T>();
}

template <typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vec) {
    // MathVector<T> result(M, N);
    // for (int i = 0; i < M; i++) {
    //   result[i] = (*thsi)[i] * vec;
    // }
    // return result;
    return MathVector<T>();
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) {
    // Matrix<T> result(M, matr.N);
    // Matrix<T> matr_t = matr.transp();
    // for (int i = 0; i < M; i++) {
    //   for (int j = 0; j < matr.N; j++) {
    //     result[i][j] = (*this)[i] * matr_t[j];
    //   }
    // }
    // return result;
    return Matrix();
}

//template <typename T>
//MathVector<T> operator*(const MathVector<T>& vec, const Matrix<T>& matrix) {
//  return MathVector<T>();
//}

//template <typename T>
//std::ostream& operator<<(std::ostream& os, const Matrix<T>& data) {
//  return os;
//}
//
//template <typename T>
//std::istream& operator>>(std::istream& is, Matrix<T>& data) {
//  return is;
//}

#endif  // LIB_MATRIX_MATRIX_H_
