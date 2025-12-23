#include <iostream>
#include <stdexcept>

template <class T>
class List {
    struct Node {
        T val;
        Node* next;
        Node(T _val) : val(_val), next(nullptr) {}
    };
    Node* _first;
    Node* _tail;
    size_t _size;

public:
    List();
    List(const List&);
    ~List();

    List& assign(const List&);
    size_t size() const { return _size; }
    bool is_empty() const { return _first == nullptr; }
    T& front() {
        if (is_empty()) throw std::logic_error("List::front: List is empty");
        return _first->val;
    }
    T& back() {
        if (is_empty()) throw std::logic_error("List::back: List is empty");
        return _tail->val;
    }

    void push_back(T);
    void push_front(T);
    void pop_front();
    void pop_back();
    void pop_by_val(T);
    void insert(size_t, const T&);
    void erase(size_t);
    void clear();
    Node* find_node_by_val(T);


    // Итераторы
    class Iterator {
        Node* _current;
    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node* node) : _current(node) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                _current = other._current;
            }
            return *this;
        }

        Iterator& operator++() {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator iter = *this;
            ++(*this);
            return iter;
        }

        bool operator==(const Iterator& other) const {
            return _current == other._current;
        }

        bool operator!=(const Iterator& other) const {
            return _current != other._current;
        }

        T& operator*() {
            if (_current == nullptr) {
                throw std::logic_error("List::Iterator.operator*: Current node is nullptr");
            }
            return _current->val;
        }

        T* operator->() {
            if (_current == nullptr) {
                throw std::logic_error("Iterator: accessing end iterator");
            }
            return &(_current->val);
        }

        Iterator& operator+=(size_t gap) {
            for (size_t i = 0; i < gap; i++) {
                if (_current == nullptr) break;
                _current = _current->next;
            }
            return *this;
        }

    };

    Iterator begin() { return Iterator(_first); }
    Iterator end() { return Iterator(nullptr); }
    const Iterator begin() const { return Iterator(_first); }
    const Iterator end() const { return Iterator(nullptr); }
    List& operator=(const List& other) { //for calculator
        if (this != &other) {
            clear();
            Node* current = other._first;
            while (current != nullptr) {
                push_back(current->val);
                current = current->next;
            }
        }
        return *this;
    }
};

// Конструкторы и деструктор
template <class T>
List<T>::List() : _first(nullptr), _tail(nullptr), _size(0) {}

template <class T>
List<T>::List(const List& other) : _first(nullptr), _tail(nullptr), _size(0) {
    Node* current = other._first;
    while (current != nullptr) {
        push_back(current->val);
        current = current->next;
    }
}

template <class T>
List<T>::~List() {
    clear();
}

// Основные операции

template<class T> List<T>& List<T>::assign(const List& other) {
    if (this != &other) {
        clear();
        //_size = 0;
        Node* current = other._first;
        while (current != nullptr) {
            push_back(current->val);
            current = current->next;
        }
    }
    return *this;
}

template <class T>
void List<T>::push_back(T _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        _first = p;
        _tail = p;
    }
    else {
        _tail->next = p;
        _tail = p;
    }
    _size++;
}

template <class T>
void List<T>::push_front(T _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        _first = p;
        _tail = p;
    }
    else {
        p->next = _first;
        _first = p;
    }
    _size++;
}

template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("List::pop_front: List is empty");
    }

    Node* d = _first;
    _first = _first->next;
    if (_first == nullptr) {
        _tail = nullptr; 
    }
    delete d;
    _size--;
}

template <class T>
void List<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("List::pop_back: List is empty");
    }

    if (_first == _tail) {
        delete _first;
        _first = nullptr;
        _tail = nullptr;
    }
    else {
        Node* p = _first;
        while (p->next->next != nullptr) {
            p = p->next;
        }
        delete _tail;
        _tail = p;
        _tail->next = nullptr;
    }
    _size--;
}

template <class T>
void List<T>::pop_by_val(T _val) {
    if (is_empty()) {
        throw std::logic_error("List::remove_by_val: List is empty");
    }

    if (_first->val == _val) {
        pop_front();
        return;
    }

    Node* prev = _first;
    Node* cur = _first->next;

    while (cur != nullptr && cur->val != _val) {
        prev = cur;
        cur = cur->next;
    }

    if (cur== nullptr) {
        throw std::logic_error("List::remove_by_val: Value not found");
    }

    if (cur == _tail) {
        _tail = prev;
    }

    prev->next = cur->next;
    delete cur;
    _size--;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
    if (pos > _size) {
        throw std::out_of_range("List::insert: Position out of range");
    }

    if (pos == 0) {
        push_front(value);
        return;
    }

    if (pos == _size) {
        push_back(value);
        return;
    }

    Node* prev = _first;
    for (size_t i = 0; i < pos - 1; i++) {
        prev = prev->next;
    }

    Node* newNode = new Node(value);
    newNode->next = prev->next;
    prev->next = newNode;
    _size++;
}

template <class T>
void List<T>::erase(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("List::erase: Position out of range");
    }

    if (is_empty()) {
        throw std::logic_error("List::erase: List is empty");
    }

    if (pos == 0) {
        pop_front();
        return;
    }

    Node* prev = _first;
    for (size_t i = 0; i < pos - 1; i++) {
        prev = prev->next;
    }

    Node* toDelete = prev->next;

    if (toDelete == _tail) {
        _tail = prev;
    }

    prev->next = toDelete->next;
    delete toDelete;
    _size--;
}

template <class T>
void List<T>::clear() {
    Node* current = _first;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    _first = nullptr;
    _tail = nullptr;
    _size = 0;
}

template <class T>
typename List<T>::Node* List<T>::find_node_by_val(T _val) {
    Node* p = _first;
    while (p != nullptr && p->val != _val) {
        p = p->next;
    }
    return p;
}
