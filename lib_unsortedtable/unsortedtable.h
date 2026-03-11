#include "../lib_tablebase/tablebase.h"
#include "../lib_TVector/TVector.h"
template<class TKey, class TVal>
class UnsortedTable : public TableBase<TKey, TVal> {
	TVector<std::pair<TKey, TVal>> _rows;

	int suppFind(const TKey& key){
		for (size_t i = 0; i < _rows.size(); i++) {
			if (_rows[i].first == key) return i;
		}
		return -1;
    }
public:
	UnsortedTable(){}
	
	bool insert(const TKey& key,const TVal& val) override{
		if (contains(key)) throw std::logic_error("Already has this key");
		_rows.push_back({ key, val });
		return true;
	}

	void remove(const TKey& key) override {
		_rows.erase(suppFind(key));
		return;
	}

	TVal* find(const TKey& key) override {
		return &_rows[suppFind(key)].second;
	}

	bool contains(const TKey& key) override{
		if (suppFind(key) != -1) return true;
		return false;
	}
	int size() override { return _rows.size(); }

	bool isEmpty() const noexcept override {
		return _rows.is_empty();
	}
};