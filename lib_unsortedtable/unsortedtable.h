#include "../lib_itable/itable.h"
#include "../lib_TVector/TVector.h"
template<class TKey, class TVal>
class UnsortedTable : public ITable<TKey, TVal> {
	TVector<std::pair<TKey, TVal>> _rows;
public:
	UnsortedTable(){}
	bool insert(const TKey& key,const TVal& val) override{
		if (contains(key)) throw std::logic_error("Already has this key");
		_rows.push_back({ key, val });
		return true;
	}

	void remove(const TKey& key) override {
		for (size_t i = 0; i < _rows.size(); i++) {
			if (key == _rows[i].first) {
				_rows.erase(i);
			}
		}
	}

	TVal* find(const TKey& key) override {
		for (size_t i = 0; i < _rows.size(); i++) {
			if (_rows[i].first == key)
				return &_rows[i].second;
		}
		return nullptr;
	}

	bool contains(const TKey& key) override{
		for (int i = 0; i < _rows.size(); i++) {
			if (key == _rows[i].first) {
				return true;
			}
		}
		return false;
	}

	bool changeVal(const TKey& key, const TVal& val) override {
		for (size_t i = 0; i < _rows.size(); ++i) {
			if (_rows[i].first == key) {
				_rows[i].second = val;
				return true;
			}
		}
		return false;
	}

	bool changeKey(const TKey& oldKey, const TKey& newKey) override {
		for (size_t i = 0; i < _rows.size(); ++i) {
			if (_rows[i].first == oldKey) {
				_rows[i].first = newKey;
				return true;
			}
		}
		return false;
	}

	int size() override{ return _rows.size(); }

	bool isEmpty() const noexcept override {
		return _rows.is_empty();
	}

};