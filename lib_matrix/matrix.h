

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>

#include "../lib_mathvector/mathvector.h"
#include "../lib_TVector/TVector.h"

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
Matrix<T>::Matrix() :_m(2), _n(2) {
    this->resize(m, )
};

template <typename T>
Matrix<T>::Matrix(size_t m, size_t n) : _m(m), _n(n) {
    this->resize(m);
    for (int i = 0; i < m; ++i) {
        
    }

}

//template <typename T>
//Matrix<T>::Matrix() : _m(2), _n(2) {
//    ;
//}

template <typename T>
Matrix<T>::~Matrix() {
    //~Matrix delete;
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
    return Matrix<T>();
}

template <typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vec) {
    return MathVector<T>();
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) {
    return Matrix();
}

#endif  // LIB_MATRIX_MATRIX_H_
