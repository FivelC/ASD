#include <iostream>
#include <initializer_list>


template <class T>
class Stack {
	T* _data; int _size; int _top;
public:
	Stack();
	Stack(int);
	Stack(const Stack<T>&);
	Stack(std::initializer_list<T>);
	~Stack();

	void push(T val);
	void pop();
	inline T top() const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;

};

template <class T>
Stack<T>::Stack() {
	_size = 10;
	_data = new T[_size];
	_top = -1;
}

template <class T>
Stack<T>::Stack(int size) {
	_size = size;
	_data = new T[_size];
	_top = -1;
}

template <class T>
Stack<T>::Stack(const Stack<T>& other) {
	_size = other._size;
	_top = other._top;
	_data = new T[_size];
	for (int i = 0; i <= _top; ++i) {
		_data[i] = other._data[i];
	}
}

template <class T>
Stack<T>::Stack(std::initializer_list<T> init_list) {
	_size = init_list.size();
	_data = new T[_size];
	_top = _size - 1;

	int i = 0;
	for (const T& val : init_list) {
		_data[i++] = val;
	}
}

template <class T>
Stack<T>::~Stack() {
	delete[] _data;
}



template <class T>
void Stack<T>::push(T val) {
	if (is_full()) throw std::logic_error("push(): Stack is full!");
	_data[++_top] = val;
}

template <class T>
void Stack<T>::pop() {
	if (is_empty()) throw std::logic_error("pop(): Stack is empty!");
	_top--;
}

template <class T>
T Stack<T>::top() const {
	if (is_empty()) throw std::logic_error("top(): Stack is empty!");
	return _data[_top];
}

template <class T>
inline bool Stack<T>::is_empty() const noexcept {
	return _top == -1;
}

template <class T>
inline bool Stack<T>::is_full() const noexcept {
	return _top == _size - 1;
}

template <class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}
