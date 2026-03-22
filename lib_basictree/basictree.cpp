#include "basictree.h"
template <typename TKey, typename TVal>
BasicTree<TKey, TVal>::BasicTree() {

}
template <typename TKey, typename TVal>
BasicTree<TKey, TVal>::~BasicTree() {

}
//////////////////////////////////////////////////////////////////
template <typename TKey, typename TVal>
void BasicTree<TKey, TVal>::insert(const TKey key, const TVal val) {
    Node* node = new Node(key, val);
    if (isEmpty()) {
        _root = node;
        return;
    }
    Node* cur = nullptr;
    Queue <Node*> q;
    q_push(_root);
    while (1) {
        cur = q.top();
        q.pop();
        if (!cur->left) { cur->left = node; return; }
        if (!cur->right) { cur->right = node; return; }
        q.push(cur->left);
        q.push(cur->right);
    }
}
template <typename TKey, typename TVal>
TVal* BasicTree<TKey, TVal>::find(const TKey& key) const noexcept{

}

template <typename TKey, typename TVal>
void BasicTree<TKey, TVal>::erase(const TKey&) {

}
template <typename TKey, typename TVal>
bool BasicTree<TKey, TVal>::isEmpty() const noexcept {

}
////////////////////////////////////////////////////////////////////
void print_w() const noexcept;
void print_DLCK() const noexcept;
void print_DLRC() const noexcept;
void print_DCLR_rec() const noexcept;