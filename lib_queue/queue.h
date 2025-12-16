#pragma once

#include <stdexcept>

#define QUEUE_DEFAULT_SIZE 1

template<class T> class Queue {
	T* _data;
	size_t _size;
	size_t _count;
	size_t _head;
	size_t _tail;
public:
	Queue();
	Queue(size_t);
	Queue(size_t, const T&);
	Queue(const Queue&);

	~Queue();

	Queue& assign(const Queue&);

	void push(T val);
	void pop();
	T& head();
	T& tail();
	const T& head() const;
	const T& tail() const;
	void clear() noexcept;

	void reserve(size_t) noexcept;
	void shrinkToFit();

	inline bool isEmpty() const noexcept { return _count == 0; };
	inline bool isFull() const noexcept { return _count == _size; };
	inline size_t sizeReal() const noexcept { return _count; }
	inline size_t size() const noexcept { return _size; }

	Queue& operator=(const Queue&);
};

// сonstructors and destruction
template<class T> Queue<T>::Queue() :
	_data(new T[QUEUE_DEFAULT_SIZE]),
	_size(QUEUE_DEFAULT_SIZE),
	_count(0),
	_head(0),
	_tail(0)
{
}

template<class T> Queue<T>::Queue(size_t size) :
	_data(nullptr),
	_size(size),
	_count(0),
	_head(0),
	_tail(0)
{
	if (size == 0) {
		throw std::invalid_argument("Queue(size): size must be > 0");
	}
	_data = new T[size];
}

template<class T> Queue<T>::Queue(size_t size, const T& value) :
	_data(nullptr),
	_size(size),
	_count(size),
	_head(0),
	_tail(_count% _size)
{
	if (size == 0) {
		throw std::invalid_argument("Queue(size, value): size must be > 0");
	}
	_data = new T[size];
	for (size_t i = 0; i < _size; i++) {
		_data[i] = value;
	}
}

template<class T> Queue<T>::Queue(const Queue& other) :
	_data(nullptr),
	_size(other._size),
	_count(other._count),
	_head(other._head),
	_tail(other._tail)
{
	_data = new T[other._size];
	for (int i = 0; i < other._size; i++) {
		_data[i] = other._data[i];
	}
}

template<class T> Queue<T>::~Queue() {
	delete[] _data;
}

// functions

template<class T> Queue<T>& Queue<T>::assign(const Queue& other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_count = other._count;
		_head = other._head;
		_tail = other._tail;
		_data = new T[_size];
		for (int i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	return *this;
}

template<class T> void Queue<T>::push(T val) {
	if (isFull()) {
		throw std::logic_error("push(val): Unable to push, queue is full");
	}
	_count++;
	_data[_tail] = val;
	_tail = (_tail + 1) % _size;
}

template<class T> void Queue<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("pop(): Unable to pop, queue is empty");
	}
	_count--;
	_head = (_head + 1) % _size;
}

template<class T> T& Queue<T>::head() {
	if (isEmpty()) {
		throw std::logic_error("head(): unable to get head element, queue is empty");
	}
	return _data[_head];
}

template<class T> T& Queue<T>::tail() {
	if (isEmpty()) {
		throw std::logic_error("tail(): unable to get last(top) element, queue is empty");
	}
	return _data[(_tail - 1 + _size) % _size];
}

// for const
template<class T> const T& Queue<T>::head() const {
	if (isEmpty()) {
		throw std::logic_error("head(): unable to get head element, queue is empty");
	}
	return _data[_head];
}

template<class T> const T& Queue<T>::tail() const {
	if (isEmpty()) {
		throw std::logic_error("tail(): unable to get last(top) element, queue is empty");
	}
	return _data[(_tail - 1 + _size) % _size];
}

template<class T> void Queue<T>::clear() noexcept {
	_count = 0;
	_head = 0;
	_tail = 0;
}


template<class T> void Queue<T>::reserve(size_t newCapacity) noexcept {
	if (newCapacity <= _size) return;//unnecessary
	if (newCapacity <= _count) return;

	T* newData = new T[newCapacity];

	for (int i = 0; i < _count; i++) {
		newData[i] = _data[(_head + i) % _size];
	}

	delete[] _data;
	_data = newData;
	_size = newCapacity;
	_head = 0;
	_tail = _count;
}

template<class T> void Queue<T>::shrinkToFit() {
	if (isEmpty()) {
		throw std::logic_error("shrinkToFit(): unable to shrink, queue is empty");
	}
	if (isFull()) return;

	T* newData = new T[_count];

	for (size_t i = 0; i < _count; i++) {
		newData[i] = _data[(_head + i) % _size];
	}

	delete[] _data;
	_data = newData;
	_size = _count;
	_head = 0;
	_tail = 0;
}

// overload

template<class T> Queue<T>& Queue<T>::operator=(const Queue& other) {
	return this->assign(other);
}