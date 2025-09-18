#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include "../lib_matrix/matrix.h"

template <typename T>
class TriangleMatrix : public Matrix<T> {
private:
	size_t _m;
	size_t _n;

public:
	TriangleMatrix();
	TriangleMatrix(size_t m, size_t n);
	~TriangleMatrix();

	TriangleMatrix<T> operator+(TriangleMatrix<T>& tr_matrix);
	TriangleMatrix<T> operator-(TriangleMatrix<T>& tr_matrix);
	TriangleMatrix<T> operator*(TriangleMatrix<T>& tr_matrix);

private:
};

template <typename T>
TriangleMatrix<T>::TriangleMatrix() : _m(0), _n(0) {
	;
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t m, size_t n) : _m(m), _n(n) {
	;
}

template <typename T>
TriangleMatrix<T>::~TriangleMatrix() {
	;
}
template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(TriangleMatrix<T>& tr_matrix) {
	return TriangleMatrix<T>();
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(TriangleMatrix<T>& tr_matrix) {
	return TriangleMatrix<T>();
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(TriangleMatrix<T>& tr_matrix) {
	return TriangleMatrix<T>();
}

#endif  // !LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
