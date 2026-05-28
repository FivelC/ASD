#include <iostream>
#include <queue>
#include <algorithm>

template <typename TKey, typename TVal>
class AVLTree {

    struct Node {
        std::pair<TKey, TVal> _data;
        Node* _left = nullptr;
        Node* _right = nullptr;
        int   _height = 1;

        Node(const TKey& k, const TVal& v) : _data(k, v) {}
    };

    Node* _root = nullptr;

public:
	AVLTree() = default;
    ~AVLTree() = default;
    void insert(const TKey& key, const TVal& val)
    {
        _root = insert(_root, key, val);
    }

    TVal* find(const TKey& k) const
    {
        Node* node = find(_root, k);
        return node ? &node->_data.second : nullptr;
    }

    void remove(const TKey& k) {
        _root = remove(_root, k);
    }
    std::vector<TKey> getKeys() const {
        std::vector<TKey> keys;
        inorder(_root, keys);
        return keys;
    }
private:
    void inorder(Node* p, std::vector<TKey>& out) const {
        if (!p) return;
        inorder(p->_left, out);
        out.push_back(p->_data.first);
        inorder(p->_right, out);
    }
    Node* insert(Node* p, const TKey& key, const TVal& val)
    {
        if (!p) return new Node(key, val);

        if (key < p->_data.first)
            p->_left = insert(p->_left, key, val);
        else if (key > p->_data.first)
            p->_right = insert(p->_right, key, val);
        else
            p->_data.second = val;

        return balance(p);
    }

    Node* find(Node* p, const TKey& k) const
    {
        if (!p) return nullptr;

        if (k < p->_data.first)
            return find(p->_left, k);
        else if (k > p->_data.first)
            return find(p->_right, k);
        else
            return p;
    }

    Node* findmin(Node* p) const
    {
        return p->_left ? findmin(p->_left) : p;
    }

    Node* removemin(Node* p)
    {
        if (!p->_left) return p->_right;
        p->_left = removemin(p->_left);
        return balance(p);
    }
    Node* remove(Node* p, const TKey& k)
    {
        if (!p) return nullptr;

        if (k < p->_data.first)
            p->_left = remove(p->_left, k);
        else if (k > p->_data.first)
            p->_right = remove(p->_right, k);
        else
        {
            Node* left = p->_left;
            Node* right = p->_right;
            delete p;

            if (!right) return left;

            Node* min = findmin(right);
            min->_right = removemin(right);
            min->_left = left;
            return balance(min);
        }

        return balance(p);
    }
    int height(Node* p) const {
        return p ? p->_height : 0;
    }
    int bfactor(Node* p)
    {
        return height(p->_right) - height(p->_left);
    }

    void fixheight(Node* p) {
		int hl = height(p->_left);
		int hr = height(p->_right);
        p->_height = (hl > hr ? hl : hr) + 1;
    }
    Node* rotateright(Node* p)
    {
        Node* q = p->_left;
        p->_left = q->_right;
        q->_right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }
    Node* rotateleft(Node* q) {
        Node* p = q->_right;
        q->_right = p->_left;
        p->_left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }
    Node* balance(Node* p)
    {
        fixheight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->_right) < 0) p->_right = rotateright(p->_right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->_left) > 0) p->_left = rotateleft(p->_left);
            return rotateright(p);
        }
        return p;
    }
};