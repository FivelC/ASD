#include <iostream>
#include <queue>
#include <stack>
#include <vector>
template <typename TKey, typename TVal>
class BSTree {

    struct Node {
        std::pair<TKey, TVal> _data;
        Node* _left = nullptr;
        Node* _right = nullptr;

        Node(const TKey& k, const TVal& v) : _data(k, v) {}
    };

    Node* _root = nullptr;


    void clear(Node* node) {
        if (!node) return;
        clear(node->_left);
        clear(node->_right);
        delete node;
    }

    void collectKeys(Node* node, std::vector<TKey>& keys) const {
        if (!node) return;
        collectKeys(node->_left, keys);
        keys.push_back(node->_data.first);
        collectKeys(node->_right, keys);
    }
public:

    BSTree() = default;

    ~BSTree() {
        clear(_root);
    }

    bool isEmpty() const noexcept {
        return _root == nullptr;
    }

/////////////////////////////////////////////////////////////////////
    void insert(const TKey key, const TVal val) {
        Node* newNode = new Node(key, val);

        if (!_root) {
            _root = newNode;
            return;
        }

        Node* cur = _root;
        while (true) {
            if (key == cur->_data.first) {
                cur->_data.second = val;
                delete newNode;
                return;
            }

            if (key < cur->_data.first) {
                if (!cur->_left) {
                    cur->_left = newNode;
                    return;
                }
                cur = cur->_left;
            }
            else {
                if (!cur->_right) {
                    cur->_right = newNode;
                    return;
                }
                cur = cur->_right;
            }
        }
    }

    TVal* find(const TKey& key) const noexcept {
        Node* cur = _root;
        while (cur) {
            if (key == cur->_data.first)
                return &cur->_data.second;
            else if (key < cur->_data.first)
                cur = cur->_left;
            else
                cur = cur->_right;
        }
        return nullptr;
    }

    void erase(const TKey& key) {
        Node* parent = nullptr;
        Node* cur = _root;
        bool isLeft = false;

        while (cur) {
            if (key == cur->_data.first) break;
            parent = cur;
            if (key < cur->_data.first) {
                cur = cur->_left;
                isLeft = true;
            }
            else {
                cur = cur->_right;
                isLeft = false;
            }
        }

        if (!cur) return; 

        if (!cur->_left && !cur->_right) {
            if (!parent)      _root = nullptr;
            else if (isLeft)  parent->_left = nullptr;
            else              parent->_right = nullptr;
            delete cur;
        }

        else if (!cur->_left) {
            if (!parent)      _root = cur->_right;
            else if (isLeft)  parent->_left = cur->_right;
            else              parent->_right = cur->_right;
            delete cur;
        }

        else if (!cur->_right) {
            if (!parent)      _root = cur->_left;
            else if (isLeft)  parent->_left = cur->_left;
            else              parent->_right = cur->_left;
            delete cur;
        }

        else {
            Node* maxParent = cur;
            Node* maxLeft = cur->_left;
            while (maxLeft->_right) {
                maxParent = maxLeft;
                maxLeft = maxLeft->_right;
            }

            cur->_data = maxLeft->_data;

            if (maxParent == cur)
                maxParent->_left = maxLeft->_left;
            else
                maxParent->_right = maxLeft->_left;

            delete maxLeft;
        }
    }
    /////////////////////////////////////////////////////////////////
    void print_tree() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            size_t levelSize = q.size();
            for (size_t i = 0; i < levelSize; i++) {
                Node* cur = q.front(); 
                q.pop();
                std::cout << cur->_data.first << ' ';
                if (cur->_left)  q.push(cur->_left);
                if (cur->_right) q.push(cur->_right);
            }
            std::cout << '\n';
        }
    }

    std::vector<TKey> getKeys() const {
        std::vector<TKey> keys;
        collectKeys(_root, keys);
        return keys;
    }
};
