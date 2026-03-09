#include "../lib_itable/itable.h"
#include "../lib_TVector/TVector.h"

template <class TKey, class TValue>
class SortedTable : public ITable<TKey, TValue> {
private:
    TVector<std::pair<TKey, TValue>> _rows;

    int binarySearch(const TKey& key) const {
        int left = 0;
        int right = _rows.size() - 1;

        while (left <= right) {
            int mid = left + (left + right) / 2;

            if (_rows[mid].first == key) {
                return mid;
            }
            if (_rows[mid].first < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }

    size_t findInsertPosition(const TKey& key) const {
        size_t left = 0;
        size_t right = _rows.size();

        while (left < right) {
            size_t mid = left + (right - left) / 2;

            if (_rows[mid].first < key) {
                left = mid - 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }

public:
    SortedTableM() = default;
    void insert(const TKey& key, const TValue& value) override {
        int index = binarySearch(key);
        if (index != -1) {
            _rows[index].second = value;
            return;
        }

        size_t pos = findInsertPosition(key);
        _rows.insert(pos, { key, value });
    }

    void erase(const TKey& key) override {
        int index = binarySearch(key);
        if (index != -1) {
            _rows.erase(index);
        }
    }

    TValue* find(const TKey& key) noexcept override {
        int index = binarySearch(key);
        if (index != -1) {
            return &_rows[index].second;
        }
        return nullptr;
    }

    bool isEmpty() const noexcept override { return _rows.is_empty(); }

    void print(std::ostream& out) const override {
        out << "SortedTableM (" << _rows.size() << " rows):\n";
        for (size_t i = 0; i < _rows.size(); ++i) {
            out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
        }
    }

    bool contains(const TKey& key) const noexcept override { return binarySearch(key) != -1; }
};