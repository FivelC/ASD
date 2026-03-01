#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <stdexcept>

template<class T>
class DoublyLinkedList {
    struct Node {
        T val;
        Node* next;
        Node* prev;
        Node(T _val) : val(_val), next(nullptr), prev(nullptr) {};
        Node(T _val, Node* _prev, Node* _next) : val(_val), prev(_prev), next(_next) {};
    };

    Node* _first;
    Node* _tail;
    size_t _size;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&);
    ~DoublyLinkedList();



    T& front() {
        if (is_empty()) throw std::logic_error("DoublyLinkedList::front: List is empty");
        return _first->val;
    }
    T& back() {
        if (is_empty()) throw std::logic_error("DoublyLinkedList::back: List is empty");
        return _tail->val;
    }
    bool is_empty() const { return _first == nullptr; };
    size_t size() const { return _size; }
    void push_back(T);
    void push_front(T);
    Node* find_node_by_val(T);
    void pop_front();
    void pop_back();
    void pop_by_val(T);
    void insert(size_t, const T&);
    void insertAtNode(Node*, const T&);
    void erase(size_t);
    Node* eraseNode(Node*);
    void clear();

    class Iterator {
        Node* _current;
        friend class DoublyLinkedList<T>;
    public:
        Iterator() : _current(nullptr) {};
        Iterator(Node* node) : _current(node) {};

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

        Iterator& operator--() {
            if (_current != nullptr) {
                _current = _current->prev;
            }
            return *this;
        }
        Iterator operator--(int) {
            Iterator iter = *this;
            --(*this);
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
                throw std::logic_error("Iterator: dereferencing end iterator");
            }
            return _current->val;
        }

        Iterator& operator+=(size_t gap) {
            for (size_t i = 0; i < gap; i++) {
                if (_current == nullptr) break;
                _current = _current->next;
            }
            return *this;
        }

        Iterator& operator-=(size_t gap) {
            for (size_t i = 0; i < gap; i++) {
                if (_current == nullptr) break;
                _current = _current->prev;
            }
            return *this;
        }

        T* operator->() {
            if (_current == nullptr) {
                throw std::logic_error("Iterator: accessing end iterator");
            }
            return &(_current->val);
        }
    };
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    Iterator erase(Iterator it) {
        return Iterator(eraseNode(it._current));
    }
    Iterator begin() { return Iterator(_first); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(_tail); }
    Iterator rend() { return Iterator(nullptr); }
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : _first(nullptr), _tail(nullptr), _size(0) {}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) :
    _first(nullptr), _tail(nullptr), _size(0) {
    Node* cur = other._first;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<class T>
void DoublyLinkedList<T>::push_back(T _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        _first = p;
        _tail = p;
    }
    else {
        _tail->next = p;
        p->prev = _tail;
        _tail = p;
    }
    _size++;
}

template<class T>
void DoublyLinkedList<T>::push_front(T _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        _first = p;
        _tail = p;
    }
    else {
        p->next = _first;
        _first->prev = p;
        _first = p;
    }
    _size++;
}

template<class T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::find_node_by_val(T _val) {
    if (is_empty()) throw std::logic_error("find_node_by_val: List is empty");;
    Node* p = _first;
    while (p && p->val != _val) {
        p = p->next;
    }
    return p;
}

template <class T>
void DoublyLinkedList<T>::pop_front() {
    if (is_empty()) throw std::logic_error("pop_front: List is empty");

    Node* p = _first;
    _first = _first->next;
    if (_first != nullptr) {
        _first->prev = nullptr;
    }
    else {
        _tail = nullptr;
    }
    delete p;
    _size--;
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
    if (is_empty()) throw std::logic_error("pop_back: List is empty");

    if (_tail == _first) {
        pop_front();
        return;
    }

    Node* newTail = _tail->prev;
    newTail->next = nullptr;
    delete _tail;
    _tail = newTail;
    _size--;
}

template <class T>
void DoublyLinkedList<T>::pop_by_val(T _val) {
    if (is_empty()) {
        throw std::logic_error("pop_by_val: List is empty");
    }

    if (_first->val == _val) {
        pop_front();
        return;
    }

    if (_tail->val == _val) {
        pop_back();
        return;
    }

    Node* current = _first;
    while (current && current->val != _val) {
        current = current->next;
    }

    if (!current) {
        throw std::logic_error("pop_by_val: Value not found");
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    _size--;
}

template<class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& value) {
    if (pos > _size) {
        throw std::out_of_range("insert: Position out of range");
    }

    if (pos == 0) {
        push_front(value);
        return;
    }

    if (pos == _size) {
        push_back(value);
        return;
    }

    Node* cur = nullptr;

    if (pos <= _size / 2) {
        cur = _first;
        for (size_t i = 0; i < pos - 1; i++) {
            cur = cur->next;
        }
    }
    else {
        cur = _tail;
        for (size_t i = _size - 1; i > pos - 1; i--) {
            cur = cur->prev;
        }
    }

    Node* newNode = new Node(value, cur, cur->next);
    cur->next->prev = newNode;
    cur->next = newNode;
    _size++;
}

template<class T>
void DoublyLinkedList<T>::insertAtNode(typename DoublyLinkedList<T>::Node* pos, const T& value) {
    if (pos == nullptr) {
        throw std::logic_error("insertAtNode: Node pointer is null");
    }

    Node* newNode = new Node(value, pos, pos->next);
    if (pos->next != nullptr) {
        pos->next->prev = newNode;
    }
    pos->next = newNode;

    if (pos == _tail) {
        _tail = newNode;
    }
    _size++;
}

template<class T>
void DoublyLinkedList<T>::erase(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("erase: Position out of range");
    }

    if (is_empty()) {
        throw std::logic_error("erase: List is empty");
    }

    if (pos == 0) {
        pop_front();
        return;
    }

    if (pos == _size - 1) {
        pop_back();
        return;
    }

    Node* cur = _first;
    for (size_t i = 0; i < pos; i++) {
        cur = cur->next;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    _size--;
}

template<class T>
typename DoublyLinkedList<T>::Node*
DoublyLinkedList<T>::eraseNode(Node* pos) {

    if (!pos)
        throw std::logic_error("eraseNode: Node pointer is null");

    if (is_empty())
        throw std::logic_error("eraseNode: List is empty");

    Node* next = pos->next;

    if (pos == _first) {
        pop_front();
        return next;
    }

    if (pos == _tail) {
        pop_back();
        return nullptr;
    }

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    delete pos;
    _size--;

    return next;
}

//template<class T>
//typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::eraseNode(typename DoublyLinkedList<T>::Node* pos) {
//    if (pos == nullptr) {
//        throw std::logic_error("eraseNode: Node pointer is null");
//    }
//
//    if (is_empty()) {
//        throw std::logic_error("eraseNode: List is empty");
//    }
//
//    if (pos == _first) {
//        pop_front();
//        return;
//    }
//
//    if (pos == _tail) {
//        pop_back();
//        return;
//    }
//
//    pos->prev->next = pos->next;
//    pos->next->prev = pos->prev;
//    delete pos;
//    _size--;
//}

template<class T>
void DoublyLinkedList<T>::clear() {
    while (_first != nullptr) {
        Node* cur = _first;
        _first = _first->next;
        delete cur;
    }
    _tail = nullptr;
    _size = 0;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        clear();

        Node* cur = other._first;
        while (cur != nullptr) {
            push_back(cur->val);
            cur = cur->next;
        }
    }
    return *this;
}
#endif // DOUBLYLINKEDLIST_H