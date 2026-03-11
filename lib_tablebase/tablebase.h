#include "../lib_itable/itable.h"

template <class TKey, class TVal>
class TableBase : public ITable<TKey, TVal> {
public:

	bool changeVal(const TKey& key, const TVal& val) override {
		if (!this->contains(key)) return false;

		*this->find(key) = val;
		return true;
	}

	bool changeKey(const TKey& oldKey, const TKey& newKey) override {

		if (!this->contains(oldKey)) return false;

		TVal value = *this->find(oldKey);

		this->remove(oldKey);
		this->insert(newKey, value);

		return true;
	}
};