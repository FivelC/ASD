#pragma once
#include <vector>
#include <stdexcept>
#include "../lib_tablebase/tablebase.h"
#include "../lib_RBtree/RBtree.h"

template <class TKey, class TVal>
class RBTable : public TableBase<TKey, TVal> {
private:
    RBTree<TKey, TVal> _tree;
    int _size = 0;

public:
    RBTable() {}

    bool insert(const TKey& key, const TVal& val) override {
        if (!_tree.insert(key, val))
            throw std::logic_error("Already has this key");
        ++_size;
        return true;
    }

    int size() override {
        return _size;
    }

    bool isEmpty() const noexcept override {
        return _size == 0;
    }

    TVal* find(const TKey& key) override {
        return _tree.find(key);
    }
    bool contains(const TKey& key) override {
        throw std::logic_error("contains: not implemented for RBTree yet");
    }
    void remove(const TKey& key) override {
        throw std::logic_error("remove: not implemented for RBTree yet");
    }
    std::vector<TKey> getKeys() {
        return _tree.getKeys();
    }
};