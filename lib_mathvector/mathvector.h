
#ifndef LIB_MATHVECTOR_MATHVECTORX_H_
#define LIB_MATHVECTOR_MATHVECTORX_H_

#include <iostream>
#include "../lib_TVector/TVector.h"

template <typename T>
class MathVector : private TVector<T> {
private:
    size_t _m;
    TVector<T> data;

public:
    MathVector();
    MathVector(size_t m);
    ~MathVector();
    MathVector<T> operator*(T& val);
    T operator*(MathVector<T>& vec);

    friend std::ostream& operator<<(std::ostream& os, const MathVector<T>& data) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, const MathVector<T>& data) {
        return is;
    }

private:
};

template <typename T>
MathVector<T>::MathVector() : TVector<T>() {
    ;
}

template <typename T>
MathVector<T>::~MathVector() {
    ;
}
template <typename T>
MathVector<T>::MathVector(size_t m) : _m(m) {
    ;
}

template <typename T>
MathVector<T> MathVector<T>::operator*(T& val) {
    MathVector<T> result(size);
    return *this;
}
template <typename T>
T MathVector<T>::operator*(MathVector<T>& vec) {
    return T();
}

#endif  // LIB_MATHVECTOR_MATHVECTORX_H_

