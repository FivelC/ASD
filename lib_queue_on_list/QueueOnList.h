#include <stdexcept>
#include "..\lib_list\list.h"
#define QUEUE_DEFAULT_SIZE 1

template<class T> class QueueOnList {
	List<T> _data;
	size_t _size;
public:
	QueueOnList();
	QueueOnList(size_t);
	QueueOnList(size_t, const T&);
	QueueOnList(const QueueOnList&);

	QueueOnList& assign(const QueueOnList&);

	void push(T val);
	void pop();
	T& head();
	T& tail();
	void clear() noexcept;

	void reserve(size_t) noexcept;
	void shrinkToFit();

	inline bool isEmpty() const noexcept { return _data.is_empty(); }
	inline bool isFull() const noexcept { return _data.size() == _size; }
	inline size_t sizeReal() const noexcept { return _data.size(); }
	inline size_t size() const noexcept { return _size; }

	QueueOnList& operator=(const QueueOnList&);
};

// сonstructors and destruction
template<class T> QueueOnList<T>::QueueOnList() :
	_size(QUEUE_DEFAULT_SIZE)
{
}

template<class T> QueueOnList<T>::QueueOnList(size_t size) :
	_size(size)
{
	if (size == 0) {
		throw std::invalid_argument("QueueOnList(size): size must be > 0");
	}
}

template<class T> QueueOnList<T>::QueueOnList(size_t size, const T& value) :
	_size(size)
{
	if (size == 0) {
		throw std::invalid_argument("QueueOnList(size, value): size must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.push_back(value);
	}
}

template<class T> QueueOnList<T>::QueueOnList(const QueueOnList& other)
	: _size(other._size), _data(other._data)
{
}

// functions

template<class T> QueueOnList<T>& QueueOnList<T>::assign(const QueueOnList& other) {
	if (this != &other) {
		_data.assign(other._data);
		_size = other.size();
	}
	return *this;
}

template<class T> void QueueOnList<T>::push(T val) {
	if (isFull()) {
		throw std::logic_error("QueueOnList.push: Unable to push - queue is full");
	}
	_data.push_back(val);
}

template<class T> void QueueOnList<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("QueueOnList.push: Unable to push - queue is empty");
	}
	_data.pop_front();
}

template<class T> T& QueueOnList<T>::head() {
	if (isEmpty()) {
		throw std::logic_error("QueueOnListt.head: Unable to get top element - queue is empty");
	}
	return _data.front();
}

template<class T> T& QueueOnList<T>::tail() {
	if (isEmpty()) {
		throw std::logic_error("QueueOnList.tail: Unable to get top element - queue is empty");
	}
	return _data.back();
}

template<class T> void QueueOnList<T>::clear() noexcept {
	_data.clear();
}


template<class T> void QueueOnList<T>::reserve(size_t newCapacity) noexcept {
	if (newCapacity <= _size) return;
	_size = newCapacity;
}

template<class T> void QueueOnList<T>::shrinkToFit() {
	_size = _data.size();
}

// overload

template<class T> QueueOnList<T>& QueueOnList<T>::operator=(const QueueOnList& other) {
	return this->assign(other);
}