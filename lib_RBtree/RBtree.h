#include <iostream>
#include <queue>
#include <algorithm>

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

    // ── вращения ──────────────────────────────────────────────
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

    // ── fixup после вставки ───────────────────────────────────
    void insertFixup(Node* z) {
        while (z->_parent && z->_parent->_color == RED) {
            Node* gp = z->_parent->_parent;   // дед
            if (z->_parent == gp->_left) {
                Node* uncle = gp->_right;
                if (uncle && uncle->_color == RED) {
                    // случай 1: дядя красный → перекраска
                    z->_parent->_color = BLACK;
                    uncle->_color = BLACK;
                    gp->_color = RED;
                    z = gp;
                }
                else {
                    if (z == z->_parent->_right) {
                        // случай 2: z — правый ребёнок → левый поворот
                        z = z->_parent;
                        rotateLeft(z);
                    }
                    // случай 3: z — левый ребёнок → правый поворот
                    z->_parent->_color = BLACK;
                    gp->_color = RED;
                    rotateRight(gp);
                }
            }
            else {
                // симметрично (parent — правый ребёнок деда)
                Node* uncle = gp->_left;
                if (uncle && uncle->_color == RED) {
                    z->_parent->_color = BLACK;
                    uncle->_color = BLACK;
                    gp->_color = RED;
                    z = gp;
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
        _root->_color = BLACK;   // инвариант: корень всегда чёрный
    }

    // ── вставка (рекурсивный BST + fixup) ────────────────────
    void bstInsert(Node* z) {
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur) {
            parent = cur;
            if (z->_data.first < cur->_data.first) cur = cur->_left;
            else if (z->_data.first > cur->_data.first) cur = cur->_right;
            else { cur->_data.second = z->_data.second; delete z; return; }
        }
        z->_parent = parent;
        if (!parent)                          _root = z;
        else if (z->_data.first < parent->_data.first) parent->_left = z;
        else                                       parent->_right = z;
    }

    // ── print (BFS по уровням) ────────────────────────────────
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

public:
    void insert(const TKey& k, const TVal& v) {
        Node* z = new Node(k, v);   // новый узел — всегда красный
        bstInsert(z);
        if (z->_parent)             // если узел не был дубликатом
            insertFixup(z);
        else if (_root == z)
            _root->_color = BLACK;
    }

    void print() const { printLevel(_root); }
};