#include "../lib_TVector/TVector.h"

#include <stdexcept>

#define STACK_DEFAULT_SIZE 1

template<class T> class Stack {
	T* _data;
	size_t _size;
	int _top;
public:
	Stack();
	Stack(size_t);
	Stack(size_t, const T&);
	Stack(const Stack&);

	~Stack();

	Stack& assign(const Stack&);
	void push(T& val);
	void pop();
	T& top();
	void clear() noexcept;

	void reserve(size_t) noexcept;
	void shrinkToFit();

	inline bool isEmpty() const noexcept { return _top == -1; }
	inline bool isFull() const noexcept { return _top == static_cast<int>(_size - 1); }
	inline size_t sizeReal() const noexcept { return static_cast<size_t>(_top + 1); }
	inline size_t size() const noexcept { return _size; }

	Stack& operator=(const Stack&);
};

// сonstructors

template<class T> Stack<T>::Stack() :
	_data(new T[STACK_DEFAULT_SIZE]),
	_size(STACK_DEFAULT_SIZE),
	_top(-1)
{
}

template<class T> Stack<T>::Stack(size_t size) :
	_data(nullptr),
	_size(size),
	_top(-1)
{
	if (size == 0) {
		throw std::logic_error("Stack(size): size must be > 0");
	}
	_data = new T[_size];
}

template<class T> Stack<T>::Stack(size_t size, const T& value) :
	_data(nullptr),
	_size(size),
	_top(static_cast<int>(size - 1))
{
	if (size == 0) {
		throw std::logic_error("Stack(size, val): size must be > 0");
	}
	_data = new T[_size];
	for (size_t i = 0; i < _size; i++) {
		_data[i] = value;
	}
}

template<class T> Stack<T>::Stack(const Stack& other) :
	_data(nullptr),
	_size(other._size),
	_top(other._top)
{
	_data = new T[_size];
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}

template<class T> Stack<T>::~Stack() {
	delete[] _data;
}


//function

template<class T> Stack<T>& Stack<T>::assign(const Stack& other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_top = other._top;
		_data = new T[_size];
		for (size_t i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	return *this;
}

template<class T> void Stack<T>::push(T& val) {
	if (isFull()) {
		throw std::logic_error("push(val): unable to push, stack is full");
	}
	_top++;
	_data[_top] = val;
}

template<class T> void Stack<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("pop(): unable to pop, stack is empty");
	}
	_top--;
}

template<class T> T& Stack<T>::top() {
	if (isEmpty()) {
		throw std::logic_error("top(): unable to get the top element, stack is empty");
	}
	return _data[_top];
}

template<class T> void Stack<T>::clear() noexcept {
	_top = -1;
}

template<class T> void Stack<T>::reserve(size_t newCapacity) noexcept {
	if (newCapacity <= _size) return;
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < _size; i++) {
		newData[i] = _data[i];
	}
	delete[] _data;
	_data = newData;
	_size = newCapacity;
}

template<class T> void Stack<T>::shrinkToFit() {
	if (isEmpty()) {
		throw std::logic_error("shrinkToFit(): undable to shrink, stack is empty");
	}
	if (isFull()) return;
	T* newData = new T[_top + 1];
	for (size_t i = 0; i <= _top; i++) {
		newData[i] = _data[i];
	}
	delete[] _data;
	_data = newData;
	_size = _top + 1;
}


// overload

template<class T> Stack<T>& Stack<T>::operator=(const Stack& other) {
	return this->assign(other);
}



















//Stack(std::initializer_list<T> list);
//template<class T> Stack<T>::Stack(std::initializer_list<T> list) :
//	_data(nullptr),
//	_size(list.size()),
//	_top(static_cast<int>(list.size() - 1))
//{
//	if (_size == 0) {
//		throw std::logic_error("Stack(initializer_list): list must not be empty");
//	}
//	_data = new T[_size];
//
//	// Копируем элементы из initializer_list
//	size_t i = 0;
//	for (const T& element : list) {
//		_data[i++] = element;
//	}
//}