#include "../lib_tablebase/tablebase.h"
#include "../lib_binarysearchtree/binarysearchtree.h"

template<class TKey, class TVal>
class SortedTreeTable : public TableBase<TKey, TVal> {

    BSTree<TKey, TVal> _tree;
    int _size = 0;

public:

    SortedTreeTable() {}

    bool insert(const TKey& key, const TVal& val) override {
        if (contains(key))
            throw std::logic_error("Already has this key");
        _tree.insert(key, val);
        _size++;
        return true;
    }

    void remove(const TKey& key) override {
        if (!contains(key))
            throw std::logic_error("Key not found");
        _tree.erase(key);
        _size--;
    }

    TVal* find(const TKey& key) override {
        return _tree.find(key);
    }

    bool contains(const TKey& key) override {
        return _tree.find(key) != nullptr;
    }

    int size() override {
        return _size;
    }

    bool isEmpty() const noexcept override {
        return _tree.isEmpty();
    }

    std::vector<TKey> getKeys() {
        return _tree.getKeys();
    }
};