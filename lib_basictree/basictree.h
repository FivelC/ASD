#include "../lib_TVector/TVector.h"
template <typename TKey, typename TVal>
class BasicTree {
	struct Node {
		std::pair<TKey, TVal> data;
		Node* left;
		Node* right;
	};
	Node* _root;
public:
	BasicTree();
	~BasicTree();
	void insert(const TKey, const TVal);
	TVal* find(const TKey&) const noexcept;
	void erase(const TKey&);
	bool isEmpty() const noexcept;

	void print_w() const noexcept;
	void print_DLCK() const noexcept;
	void print_DLRC() const noexcept;
	void print_DCLR_rec() const noexcept;
};