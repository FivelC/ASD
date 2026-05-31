#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
template <typename TKey, typename TVal>
class RBTree {
    enum Color { RED, BLACK };

    struct Node {
        std::pair<TKey, TVal> _data;
        Node* _left = nullptr;
        Node* _right = nullptr;
        Node* _parent = nullptr;
        Color _color = RED;

        Node(const TKey& k, const TVal& v)
            : _data(k, v) {
        }
    };

    Node* _root = nullptr;

public:
    bool insert(const TKey& k, const TVal& v) {
        Node* z = new Node(k, v);
        if (!bstInsert(z))
            return false;
        insertFixup(z);
        _root->_color = BLACK;
        return true;
    }

    TVal* find(const TKey& k) const
    {
        Node* node = find(_root, k);
        return node ? &node->_data.second : nullptr;
    }

    void print() const { printLevel(_root); }

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
    void rotateLeft(Node* x) {
        Node* y = x->_right;
        x->_right = y->_left;
        if (y->_left) y->_left->_parent = x;
        y->_parent = x->_parent;
        if (!x->_parent)           _root = y;
        else if (x == x->_parent->_left) x->_parent->_left = y;
        else                             x->_parent->_right = y;
        y->_left = x;
        x->_parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->_left;
        x->_left = y->_right;
        if (y->_right) y->_right->_parent = x;
        y->_parent = x->_parent;
        if (!x->_parent)            _root = y;
        else if (x == x->_parent->_right) x->_parent->_right = y;
        else                              x->_parent->_left = y;
        y->_right = x;
        x->_parent = y;
    }

    void insertFixup(Node* z) {
        if (!z->_parent || z->_parent->_color == BLACK)
            return;

        Node* gp = z->_parent->_parent;

        if (z->_parent == gp->_left) {
            Node* uncle = gp->_right;
            if (uncle && uncle->_color == RED) {
                z->_parent->_color = BLACK;
                uncle->_color = BLACK;
                gp->_color = RED;
                insertFixup(gp);
            }
            else {
                if (z == z->_parent->_right) {    
                    z = z->_parent;
                    rotateLeft(z);
                }
                z->_parent->_color = BLACK;          
                gp->_color = RED;
                rotateRight(gp);
            }
        }
        else {  
            Node* uncle = gp->_left;
            if (uncle && uncle->_color == RED) {   
                z->_parent->_color = BLACK;
                uncle->_color = BLACK;
                gp->_color = RED;
                insertFixup(gp);
            }
            else {
                if (z == z->_parent->_left) {       
                    z = z->_parent;
                    rotateRight(z);
                }
                z->_parent->_color = BLACK;         
                gp->_color = RED;
                rotateLeft(gp);
            }
        }
    }

    bool bstInsert(Node* z) {
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur) {
            parent = cur;
            if (z->_data.first < cur->_data.first) cur = cur->_left;
            else if (z->_data.first > cur->_data.first) cur = cur->_right;
            else { cur->_data.second = z->_data.second; delete z; return false; }
        }
        z->_parent = parent;
        if (!parent) _root = z;
        else if (z->_data.first < parent->_data.first) parent->_left = z;
        else parent->_right = z;
        return true;
    }

    void printLevel(Node* root) const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                Node* n = q.front(); q.pop();
                std::cout << n->_data.first
                    << (n->_color == RED ? "R" : "B") << " ";
                if (n->_left)  q.push(n->_left);
                if (n->_right) q.push(n->_right);
            }
            std::cout << "\n";
        }
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

};