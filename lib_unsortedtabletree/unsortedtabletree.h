#include "../lib_tablebase/tablebase.h"
#include "../lib_basictree/basictree.h"
template<class TKey, class TVal>
class UnsortedTableTree : public TableBase<TKey, TVal> {
	BasicTree<TKey, TVal> _rows;
	int _size = 0;
public:
    UnsortedTableTree() {}

    bool insert(const TKey& key, const TVal& val) override {
        if (contains(key))
            throw std::logic_error("Already has this key");
        _rows.insert(key, val);
        _size++;
        return true;
    }

    void remove(const TKey& key) override {
        if (!contains(key))
            throw std::logic_error("Key not found");
        _rows.erase(key);
        _size--;
    }

    TVal* find(const TKey& key) override {
        return _rows.find(key);
    }

    bool contains(const TKey& key) override {
        return _rows.find(key) != nullptr;
    }

    int size() override {
        return _size;
    }

    bool isEmpty() const noexcept override {
        return _rows.is_empty();
    }
};