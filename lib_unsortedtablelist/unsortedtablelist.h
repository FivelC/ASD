#include "../lib_tablebase/tablebase.h"
#include "../lib_TVector/TVector.h"
#include "../lib_doubly_linked_list/DoublyLinkedList.h"
template<class TKey, class TVal>
class UnsortedTable : public TableBase<TKey, TVal> {
	DoublyLinkedList<std::pair<TKey, TVal>> _rows;
	typename DoublyLinkedList<std::pair<TKey, TVal>>::Iterator suppFind(const TKey& key) {
		for (auto it = _rows.begin(); it != _rows.end(); ++it) {
			if (it->first == key) return it;
		}
		return _rows.end();;
	}
public:
	UnsortedTable(){}
	bool insert(const TKey& key,const TVal& val) override{
		if (contains(key)) throw std::logic_error("Already has this key");
		_rows.push_back({ key, val });
		return true;
	}

	void remove(const TKey& key) override {
		auto it = suppFind(key);
		if (it == _rows.end())
			throw std::logic_error("Key not found");
		_rows.erase(it);
	}

	TVal* find(const TKey& key) override {
		auto it = suppFind(key);
		if (it == _rows.end())
			return nullptr;
		return &(it->second);
	}

	bool contains(const TKey& key) override {
		return suppFind(key) != _rows.end();
	}

	int size() override { return _rows.size(); }

	bool isEmpty() const noexcept override {
		return _rows.is_empty();
	}
};