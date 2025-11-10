#include <iostream>

template <class T>
class List {
private:
    struct Node {
        T value;
        Node* next;

        Node(T val, Node* nxt = nullptr) : value(val), next(nxt) {};
    };

    Node* _head, * _tail;

public:
    List();
    List(const List<T>&);
    ~List();

    bool is_empty();
    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void insert_after(Node* node, const T& value);
    void insert(size_t pos, const T& value);
    void pop_back();

    class Iterator {
        Node* _current;

    public:
        Iterator() : _current(nullptr) {};
        Iterator(Node* node) : _current(node) {};

        Iterator& operator=(const Iterator& other) noexcept {
            _current = other._current;
            return *this;
        }

        Iterator& operator++() noexcept {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }

        Iterator operator++(int) noexcept {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return _current != other._current;
        }

        bool operator==(const Iterator& other) const noexcept {
            return _current == other._current;
        }

        T& operator*() {
            if (_current == nullptr) {
                throw std::runtime_error(
                    "List::Iterator.operator*(): Dereferencing end iterator");
            }
            return _current->value;
        }

        T* operator->() {
            if (_current == nullptr) {
                throw std::runtime_error(
                    "List::Iterator.operator->(): Accessing end iterator");
            }
            return &(_current->value);
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }
    };

    inline Iterator begin();
    inline Iterator end();
};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr) {};

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr) {
    Node* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>::~List() {
    while (_head != nullptr) {
        Node* temp = _head;
        _head = _head->next;
        delete temp;
    }
}

template <class T>
bool List<T>::is_empty() {
    return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
    Node* node = new Node(value, _head);
    if (is_empty()) {
        _tail = node;
    }
    _head = node;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node* node = new Node(val, nullptr);

    if (is_empty()) {
        _head = node;
        _tail = node;
        return;
    }
    _tail->next = node;
    _tail = node;
}

template <class T>
void List<T>::insert_after(Node* node, const T& val) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("List.insert(): List is empty");
    }
    Node* new_node = new Node(val);
    new_node->next = node->next;
    node->next = new_node;
    if (node == _tail) {
        _tail = new_node;
    }
}

template <class T>
void List<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        push_front(val);
        return;
    }

    Node* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1) {
            break;
        }
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr) {
        throw std::logic_error("List.insert(): Position out of range");
    }
    insert_after(cur, val);
}

template <class T>
void List<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("List.pop_back(): List is empty");
    }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        return;
    }
    Node* cur = _head;
    while (cur->next != _tail) {
        cur = cur->next;
    }
    delete _tail;
    _tail = cur;
    cur->next = nullptr;
}

template <class T>
inline typename List<T>::Iterator List<T>::begin() {
    return Iterator(_head);
}

template <class T>
inline typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}