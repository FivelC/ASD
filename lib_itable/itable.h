template<class TKey, class TVal>
class ITable {
public:
	virtual bool insert(const TKey& key, const TVal& val) = 0;
	virtual void remove(const TKey& key) = 0;
	virtual bool contains(const TKey& key) = 0;
	virtual TVal* find(const TKey& key) = 0;
	virtual bool changeVal(const TKey& key, const TVal& val) = 0;
	virtual bool changeKey(const TKey& oldKey, const TKey& newKey) = 0;
	virtual int size() = 0;
	virtual bool isEmpty() const noexcept = 0;
	virtual ~ITable(){}
};