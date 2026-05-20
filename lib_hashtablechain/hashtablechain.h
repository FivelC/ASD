#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <type_traits>
#include "../lib_basehash/basehash.h"

template <typename TKey, typename TVal>
class HashChain : public BaseHash<TKey, TVal> {
    struct Cell {
        std::list<std::pair<TKey, TVal>> chain;
    };

    std::vector<Cell> table;

    void rehash() {
        size_t newCapacity = this->nextPrime(this->_capacity * 2);
        std::vector<Cell> newTable(newCapacity);
        size_t oldCapacity = this->_capacity;
        this->_capacity = newCapacity;
        for (size_t i = 0; i < oldCapacity; ++i) {
            for (auto& pair : table[i].chain) {
                size_t index = this->hash1(pair.first);
                newTable[index].chain.push_back(pair);
            }
        }
        table = std::move(newTable);
    }

public:
    HashChain(size_t capacity) : BaseHash<TKey, TVal>(capacity) {
        table.resize(this->_capacity);
    }
    ~HashChain() = default;

    void insert(const std::pair<TKey, TVal>& data) {
        if ((double)this->_size / this->_capacity > 0.7)
            rehash();
        size_t index = this->hash1(data.first);
        for (auto& pair : table[index].chain) {
            if (pair.first == data.first) {
                pair.second = data.second;
                return;
            }
        }
        table[index].chain.push_back(data);
        ++this->_size;
    }

    TVal* find(const TKey& key) {
        size_t index = this->hash1(key);
        for (auto& pair : table[index].chain) {
            if (pair.first == key)
                return &pair.second;
        }
        return nullptr;
    }

    int remove(const TKey& key) {
        size_t index = this->hash1(key);
        for (auto it = table[index].chain.begin(); it != table[index].chain.end(); ++it) {
            if (it->first == key) {
                table[index].chain.erase(it);
                --this->_size;
                return 0;
            }
        }
        return -1;
    }
};