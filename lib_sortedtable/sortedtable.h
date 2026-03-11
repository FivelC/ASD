#include "../lib_tablebase/tablebase.h"
#include "../lib_TVector/TVector.h"

template <class TKey, class TVal>
class SortedTable : public TableBase<TKey, TVal> {
private:
    TVector<std::pair<TKey, TVal>> _rows;

	int binarySearch(const TKey& key) const {
		size_t pos = findNearestPosition(key);
		if (pos < _rows.size() && _rows[pos].first == key) {
			return (int)pos;
		}
		return -1;
	}

	size_t findNearestPosition(const TKey& key) const {
		size_t left = 0;
		size_t right = _rows.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (_rows[mid].first < key) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		return left;
	}
public:
	SortedTable() {}

	TKey& getKeyAt(size_t index) const {
		return _rows[index].first;
	}

	bool insert(const TKey& key, const TVal& val) override {
		if (contains(key)) throw std::logic_error("Already has this key");
		size_t pos = findNearestPosition(key);

		_rows.insert(pos, {key, val});
		return true;
	}

	void remove(const TKey& key) override {
		_rows.erase(findNearestPosition(key));
		return;
	}
	TVal* find(const TKey& key) override {
		int index = binarySearch(key);
		if (index != -1) {
			return &_rows[index].second;
		}
		return nullptr;
	}

	bool contains(const TKey& key) override {
		return binarySearch(key) != -1;
	}

	int size() override { return _rows.size(); }

	bool isEmpty() const noexcept override {
		return _rows.is_empty();
	}
};