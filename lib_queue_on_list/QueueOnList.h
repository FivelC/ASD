#include "../lib_TVector/TVector.h"
#include "../lib_list/List.h"
#include "../lib_queue/Queue.h"

#include <stdexcept>
#include <initializer_list>

#define QUEUE_DEFAULT_SIZE 10

template<class T> class ListBasedQueue {
	List<T> _data;
	size_t _size;
public:
	// Constructors
	ListBasedQueue();
	ListBasedQueue(size_t);
	ListBasedQueue(size_t, const T&);
	ListBasedQueue(const TVector<T>&);
	ListBasedQueue(const std::initializer_list<T>);
	ListBasedQueue(const ListBasedQueue&);

	// Functions
	ListBasedQueue& assign(const ListBasedQueue&);
	ListBasedQueue& assign(const TVector<T>&);
	TVector<T> toTVector() const;
	Queue<T> toQueue() const;

	void push(T val);
	void pop();
	T& head();
	T& tail();
	const T& head() const;
	const T& tail() const;
	void clear() noexcept;

	void reserve(size_t) noexcept;
	void shrinkToFit();

	// Getters
	inline bool isEmpty() const noexcept { return _data.isEmpty(); };
	inline bool isFull() const noexcept { return _data.size() == _size; };
	inline size_t size() const noexcept { return _data.size(); }
	inline size_t capacity() const noexcept { return _size; }

	// Operators overload
	ListBasedQueue& operator=(const ListBasedQueue&);
	ListBasedQueue<T>& operator=(const TVector<T>&);
};

// Constructors

template<class T> ListBasedQueue<T>::ListBasedQueue() :
	_size(QUEUE_DEFAULT_SIZE)
{
}

template<class T> ListBasedQueue<T>::ListBasedQueue(size_t size) :
	_size(size)
{
	if (size == 0) {
		throw std::invalid_argument("ListBasedQueue.size_constructor: 'size' must be > 0");
	}
}

template<class T> ListBasedQueue<T>::ListBasedQueue(size_t size, const T& value) :
	_size(size)
{
	if (size == 0) {
		throw std::invalid_argument("Queue.size_constructor: 'size' must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.pushBack(value);
	}
}

template<class T> ListBasedQueue<T>::ListBasedQueue(const TVector<T>& vector) :
	_size(vector.size())
{
	if (vector.size() == 0) {
		throw std::invalid_argument("ListBasedQueue.fromTVector_constructor: 'size' must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.pushBack(vector[i]);
	}
}

template<class T> ListBasedQueue<T>::ListBasedQueue(const std::initializer_list<T> init) :
	_size(init.size())
{
	if (init.size() == 0) {
		throw std::invalid_argument("ListBasedQueue.fromInitializeList_constructor: 'size' must be > 0");
	}
	size_t i = 0;
	for (const auto& elem : init) {
		_data.pushBack(elem);
	}
}

template<class T> ListBasedQueue<T>::ListBasedQueue(const ListBasedQueue& other) :
	_size(other._size)
{
	_data = other._data;
}

// Functions

template<class T> ListBasedQueue<T>& ListBasedQueue<T>::assign(const ListBasedQueue& other) {
	if (this != &other) {
		_data.assign(other._data);
		_size = other._size;
	}
	return *this;
}

template<class T> ListBasedQueue<T>& ListBasedQueue<T>::assign(const TVector<T>& vector) {
	_data.assign(vector);
	_size = vector.size();
	return *this;
}

template<class T> TVector<T> ListBasedQueue<T>::toTVector() const {
	return _data.toTVector();
}

template<class T> Queue<T> ListBasedQueue<T>::toQueue() const {
	Queue<T> result(_data.size());
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		result.push(*it);
	}
	return result;
}

template<class T> void ListBasedQueue<T>::push(T val) {
	if (isFull()) {
		throw std::logic_error("ListBasedQueue.push: Unable to push - Queue is full");
	}
	_data.pushBack(val);
}

template<class T> void ListBasedQueue<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedQueue.pop: Unable to pop - Queue is empty");
	}
	_data.popFront();
}

template<class T> T& ListBasedQueue<T>::head() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedQueue.head: Unable to get head element - Queue is empty");
	}
	return _data.front();
}

template<class T> T& ListBasedQueue<T>::tail() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedQueue.top: Unable to get top element - Queue is empty");
	}
	return _data.back();
}

template<class T> const T& ListBasedQueue<T>::head() const {
	if (isEmpty()) {
		throw std::logic_error("ListBasedQueue.head: Unable to get head element - Queue is empty");
	}
	return _data.front();
}

template<class T> const T& ListBasedQueue<T>::tail() const {
	if (isEmpty()) {
		throw std::logic_error("ListBasedQueue.top: Unable to get top element - Queue is empty");
	}
	return _data.back();
}

template<class T> void ListBasedQueue<T>::clear() noexcept {
	_data.clear();
}

template<class T> void ListBasedQueue<T>::reserve(size_t newCapacity) noexcept {
	if (newCapacity <= _size) return;
	_size = newCapacity;
}

template<class T> void ListBasedQueue<T>::shrinkToFit() {
	if (isEmpty()) {
		throw std::logic_error("Queue.shrinkToFit: Unable to shrink - Queue is empty");
	}
	if (isFull()) return;
	_size = _data.size();
}

// Operators overload

template<class T> ListBasedQueue<T>& ListBasedQueue<T>::operator=(const ListBasedQueue& other) {
	return this->assign(other);
}

template<class T> ListBasedQueue<T>& ListBasedQueue<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}