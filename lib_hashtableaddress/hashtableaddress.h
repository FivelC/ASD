#include <iostream>
#include <vector>
#include <string>
#include "../lib_basehash/basehash.h"

enum class State {
    Empty,
    Occupied,
    Deleted
};

template <typename TKey, typename TVal>
class HashDouble : public BaseHash<TKey, TVal> {
    struct Cell {
        std::pair<TKey, TVal> data;
        State state = State::Empty;
    };

    std::vector<Cell> table;

    size_t hash2(const TKey& key) const {
        if (this->_capacity <= 2) return 1;
        const std::string str = this->toString(key);
        size_t hash = 5381;
        for (size_t i = 0; i < str.size(); ++i)
            hash = hash * 31 + str[i];
        hash = hash % (this->_capacity - 1);
        return (hash == 0) ? 1 : hash;
    }

    void rehash() {
        size_t newCapacity = this->nextPrime(this->_capacity * 2);
        std::vector<Cell> newTable(newCapacity);
        size_t oldCapacity = this->_capacity;
        this->_capacity = newCapacity;
        for (size_t i = 0; i < oldCapacity; ++i) {
            if (table[i].state == State::Occupied) {
                size_t h1 = this->hash1(table[i].data.first);
                size_t h2 = hash2(table[i].data.first);
                size_t index = h1;
                for (size_t j = 0; j < newCapacity; ++j) {
                    if (newTable[index].state != State::Occupied) {
                        newTable[index] = table[i];
                        break;
                    }
                    index = (h1 + (j + 1) * h2) % newCapacity;
                }
            }
        }
        table = std::move(newTable);
    }

public:
    HashDouble(size_t capacity) : BaseHash<TKey, TVal>(capacity) {
        table.resize(this->_capacity);
    }
    ~HashDouble() = default;

    void insert(const std::pair<TKey, TVal>& data) {
        if ((double)this->_size / this->_capacity > 0.7)
            rehash();

        size_t h1 = this->hash1(data.first);
        size_t h2 = hash2(data.first);
        size_t index = h1;
        int firstDeleted = -1;

        for (size_t i = 0; i < this->_capacity; ++i) {
            if (table[index].state == State::Occupied) {
                if (table[index].data.first == data.first) {
                    table[index].data.second = data.second;
                    return;
                }
            }
            else if (table[index].state == State::Deleted) {
                if (firstDeleted == -1) firstDeleted = (int)index;
            }
            else {
                size_t targetIndex = (firstDeleted != -1) ? (size_t)firstDeleted : index;
                table[targetIndex].data = data;
                table[targetIndex].state = State::Occupied;
                ++this->_size;
                return;
            }
            index = (h1 + (i + 1) * h2) % this->_capacity;
        }

        if (firstDeleted != -1) {
            table[firstDeleted].data = data;
            table[firstDeleted].state = State::Occupied;
            ++this->_size;
        }
    }

    TVal* find(const TKey& key) {
        size_t h1 = this->hash1(key);
        size_t h2 = hash2(key);
        size_t index = h1;
        for (size_t i = 0; i < this->_capacity; ++i) {
            if (table[index].state == State::Occupied) {
                if (table[index].data.first == key)
                    return &table[index].data.second;
            }
            else if (table[index].state == State::Empty) {
                return nullptr;
            }
            index = (h1 + (i + 1) * h2) % this->_capacity;
        }
        return nullptr;
    }

    int remove(const TKey& key) {
        size_t h1 = this->hash1(key);
        size_t h2 = hash2(key);
        size_t index = h1;
        for (size_t i = 0; i < this->_capacity; ++i) {
            if (table[index].state == State::Occupied) {
                if (table[index].data.first == key) {
                    table[index].state = State::Deleted;
                    --this->_size;
                    return 0;
                }
            }
            else if (table[index].state == State::Empty) {
                return -1;
            }
            index = (h1 + (i + 1) * h2) % this->_capacity;
        }
        return -1;
    }
};