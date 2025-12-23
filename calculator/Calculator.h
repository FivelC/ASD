#include "../lib_TVector/TVector.h"
#include "../lib_List/List.h"
#include "../lib_stack/stack.h"

#include <stdexcept>
#include <initializer_list>

#define STACK_DEFAULT_SIZE 10

template<class T> class ListBasedStack {
    List<T> _data;
    size_t _capacity; // Переименовал для ясности
public:
    // Constructors
    ListBasedStack();
    ListBasedStack(size_t capacity);
    ListBasedStack(size_t capacity, const T& value);
    ListBasedStack(const TVector<T>& vector);
    ListBasedStack(const std::initializer_list<T>& init);
    ListBasedStack(const ListBasedStack& other);

    // Functions
    Stack<T> toStack() const;

    void push(const T& val);
    void pop();
    T& top();
    const T& top() const;
    void clear() noexcept;

    void reserve(size_t newCapacity) noexcept;
    void shrinkToFit();

    // Getters
    inline bool isEmpty() const noexcept { return _data.is_empty(); }
    inline bool isFull() const noexcept { return _data.size() == _capacity; }
    inline size_t size() const noexcept { return _data.size(); }
    inline size_t capacity() const noexcept { return _capacity; }

    // Operators overload
    ListBasedStack& operator=(const ListBasedStack& other);
    ListBasedStack& operator=(const TVector<T>& vector);
};

// Constructors

template<class T>
ListBasedStack<T>::ListBasedStack() :
    _capacity(STACK_DEFAULT_SIZE)
{
}

template<class T>
ListBasedStack<T>::ListBasedStack(size_t capacity) :
    _capacity(capacity)
{
    if (capacity == 0) {
        throw std::invalid_argument("ListBasedStack: capacity must be > 0");
    }
}

template<class T>
ListBasedStack<T>::ListBasedStack(size_t capacity, const T& value) :
    _capacity(capacity)
{
    if (capacity == 0) {
        throw std::invalid_argument("ListBasedStack: capacity must be > 0");
    }
    for (size_t i = 0; i < capacity; i++) {
        _data.push_front(value);
    }
}

template<class T>
ListBasedStack<T>::ListBasedStack(const TVector<T>& vector) :
    _capacity(vector.size())
{
    if (vector.size() == 0) {
        throw std::invalid_argument("ListBasedStack: vector size must be > 0");
    }
    // Вставляем в обратном порядке, чтобы первый элемент вектора был на вершине стека
    for (size_t i = vector.size(); i > 0; i--) {
        _data.push_front(vector[i - 1]);
    }
}

template<class T>
ListBasedStack<T>::ListBasedStack(const std::initializer_list<T>& init) :
    _capacity(init.size())
{
    if (init.size() == 0) {
        throw std::invalid_argument("ListBasedStack: initializer list must not be empty");
    }
    // Вставляем в обратном порядке
    auto it = init.end();
    while (it != init.begin()) {
        --it;
        _data.push_front(*it);
    }
}

template<class T>
ListBasedStack<T>::ListBasedStack(const ListBasedStack& other) :
    _capacity(other._capacity),
    _data(other._data)  // Используем конструктор копирования списка
{
}

// Functions

template<class T>
Stack<T> ListBasedStack<T>::toStack() const {
    Stack<T> result(_data.size());

    // Создаем стек в правильном порядке (LIFO)
    // Нужно скопировать элементы в обратном порядке
    ListBasedStack<T> temp(*this);
    while (!temp.isEmpty()) {
        result.push(temp.top());
        temp.pop();
    }

    return result;
}

template<class T>
void ListBasedStack<T>::push(const T& val) {
    if (isFull()) {
        throw std::logic_error("ListBasedStack::push: stack is full");
    }
    _data.push_front(val);
}

template<class T>
void ListBasedStack<T>::pop() {
    if (isEmpty()) {
        throw std::logic_error("ListBasedStack::pop: stack is empty");
    }
    _data.pop_front();
}

template<class T>
T& ListBasedStack<T>::top() {
    if (isEmpty()) {
        throw std::logic_error("ListBasedStack::top: stack is empty");
    }
    return _data.front();
}

template<class T>
const T& ListBasedStack<T>::top() const {
    if (isEmpty()) {
        throw std::logic_error("ListBasedStack::top: stack is empty");
    }
    return _data.front();
}

template<class T>
void ListBasedStack<T>::clear() noexcept {
    _data.clear();
}

template<class T>
void ListBasedStack<T>::reserve(size_t newCapacity) noexcept {
    if (newCapacity <= _capacity) return;
    _capacity = newCapacity;
}

template<class T>
void ListBasedStack<T>::shrinkToFit() {
    if (isEmpty()) {
        throw std::logic_error("ListBasedStack::shrinkToFit: stack is empty");
    }
    if (isFull()) return;
    _capacity = _data.size();
}

// Operators overload

template<class T>
ListBasedStack<T>& ListBasedStack<T>::operator=(const ListBasedStack& other) {
    if (this != &other) {
        _capacity = other._capacity;
        _data = other._data;
    }
    return *this;
}

template<class T>
ListBasedStack<T>& ListBasedStack<T>::operator=(const TVector<T>& vector) {
    _capacity = vector.size();
    _data.clear();

    // Вставляем в обратном порядке
    for (size_t i = vector.size(); i > 0; i--) {
        _data.push_front(vector[i - 1]);
    }

    return *this;
}