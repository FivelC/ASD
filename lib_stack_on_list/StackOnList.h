#include "../lib_TVector/TVector.h"
#include "..\lib_list\list.h"
#include <stdexcept>

#define STACK_DEFAULT_SIZE 100

template<class T> class StackOnList {
	List<T> _data;
	size_t _size;
public:
	StackOnList();
	StackOnList(size_t);
	StackOnList(size_t, const T&);
	StackOnList(const StackOnList&);

	StackOnList& assign(const StackOnList&);
	void push(const T& val);
	void pop();
	T& top();
	void clear() noexcept;

	inline bool isEmpty() const noexcept { return _data.is_empty(); }
	inline bool isFull() const noexcept { return _data.size() == _size; }
	inline size_t sizeReal() const noexcept { return _data.size();}
	inline size_t size() const noexcept { return _size; }

	StackOnList& operator=(const StackOnList&);
};

// сonstructors

template<class T> StackOnList<T>::StackOnList() :
	_size(STACK_DEFAULT_SIZE)
{
}

template<class T> StackOnList<T>::StackOnList(size_t size) :
	_size(size)
{
	if (size == 0) {
		throw std::logic_error("StackOnList(size): size must be > 0");
	}
}

template<class T> StackOnList<T>::StackOnList(size_t size, const T& value) :
	_size(size)
{
	if (size == 0) {
		throw std::logic_error("StackOnList(size, val): size must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.push_back(value);
	}
}

template<class T>
StackOnList<T>::StackOnList(const StackOnList<T>& other)
	: _size(other._size), _data(other._data)
{
}


//function

template<class T> StackOnList<T>& StackOnList<T>::assign(const StackOnList& other) {
	if (this != &other) {
		_data.assign(other._data);
		_size = other.size();
	}
	return *this;
}

template<class T> void StackOnList<T>::push(const T& val) {
	if (isFull()) {
		throw std::logic_error("StackOnList.push: Unable to push - stack is full");
	}
	_data.push_back(val);
}

template<class T> void StackOnList<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("StackOnList.pop: Unable to pop - stack is empty");
	}
	_data.pop_back();
}

template<class T> T& StackOnList<T>::top() {
	if (isEmpty()) {
		throw std::logic_error("StackOnList.top: Unable to get top element - stack is empty");
	}
	return _data.back();
}

template<class T> void StackOnList<T>::clear() noexcept {
	_data.clear();
}


// overload

template<class T> StackOnList<T>& StackOnList<T>::operator=(const StackOnList& other) {
	return this->assign(other);
}