#include <iostream>
#include <queue>
#include <stack>   
#include <utility> 

template <typename TKey, typename TVal>
class BasicTree {
    struct Node {
        std::pair<TKey, TVal> _data;
        Node* _left = nullptr;
        Node* _right = nullptr;

        Node(const TKey& k, const TVal& v)
            : _data(k, v) {
        }
    };

    Node* _root = nullptr;


    void inorder(Node* node) const noexcept {
        if (!node) return;
        inorder(node->_left);
        std::cout << node->_data.first << ":" << node->_data.second << "  ";
        inorder(node->_right);
    }
public:

    BasicTree() = default;

    ~BasicTree() {
        if (!_root) return;

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            if (cur->_left)  q.push(cur->_left);
            if (cur->_right) q.push(cur->_right);
            delete cur;
        }
    }
    /////////////////////////////////////////////////////////////////
    bool is_empty() const noexcept {
        return _root == nullptr;
    }

    void insert(const TKey key, const TVal val) {
        if (!_root) {
            _root = new Node(key, val);
            return;
        }

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            if (cur->_data.first == key) {
                cur->_data.second = val;
                return;
            }

            if (!cur->_left) {
                cur->_left = new Node(key, val);
                return;
            }
            q.push(cur->_left);

            if (!cur->_right) {
                cur->_right = new Node(key, val);
                return;
            }
            q.push(cur->_right);
        }
    }


    TVal* find(const TKey& key) const noexcept {
        if (!_root) return nullptr;

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            if (cur->_data.first == key)
                return &cur->_data.second;

            if (cur->_left)  q.push(cur->_left);
            if (cur->_right) q.push(cur->_right);
        }

        return nullptr;
    }

    void erase(const TKey& key) {
        if (!_root) return;

        Node* target = nullptr;
        Node* last = nullptr;
        Node* lastParent = nullptr;
        bool  lastIsLeft = false;

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            if (cur->_data.first == key) target = cur;      

            if (cur->_left) {
                lastParent = cur;
                lastIsLeft = true;
                last = cur->_left;
                q.push(cur->_left);
            }
            if (cur->_right) {
                lastParent = cur;
                lastIsLeft = false;
                last = cur->_right;
                q.push(cur->_right);
            }
        }

        if (!target) return;

        if (last == nullptr) {
            _root = nullptr;
            delete target;
            return;
        }

        target->_data = last->_data;
        if (lastIsLeft) lastParent->_left = nullptr;
        else            lastParent->_right = nullptr;
        delete last;
    }

    //////////////////////////////////////////////////////////////////////////////////////////

    void print_w() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }

        std::queue<Node*> q;
        q.push(_root);

        std::cout << "[BFS / levels]\n";

        while (!q.empty()) {
            size_t levelSize = q.size();

            for (size_t i = 0; i < levelSize; ++i) {
                Node* cur = q.front();
                q.pop();

                std::cout << cur->_data.first << ":" << cur->_data.second;
                if (i + 1 < levelSize) std::cout << "  ";

                if (cur->_left)  q.push(cur->_left);
                if (cur->_right) q.push(cur->_right);
            }
            std::cout << '\n';
        }
    }

    void print_DCLR() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }

        std::stack<Node*> s;
        s.push(_root);

        std::cout << "[Pre-order(CLR):]\n";

        while (!s.empty()) {
            Node* cur = s.top();
            s.pop();

            std::cout << cur->_data.first << ":" << cur->_data.second << "  ";

            if (cur->_right) s.push(cur->_right);
            if (cur->_left)  s.push(cur->_left);
        }
        std::cout << '\n';
    }

    void print_DLRC() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }

        std::stack<Node*> traverse;
        std::stack<Node*> result;

        traverse.push(_root);

        while (!traverse.empty()) {
            Node* cur = traverse.top();
            traverse.pop();

            result.push(cur);

            if (cur->_left)  traverse.push(cur->_left);
            if (cur->_right) traverse.push(cur->_right);
        }

        std::cout << "[Post-order(LRC): ]\n";

        while (!result.empty()) {
            Node* cur = result.top();
            result.pop();
            std::cout << cur->_data.first << ":" << cur->_data.second << "  ";
        }
        std::cout << '\n';
    }

    void print_DLCR() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }
        std::stack<Node*> s;
        Node* cur = _root;
        std::cout << "[In-order(LCR): ]\n";
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->_left;
            }
            cur = s.top();
            s.pop();
            std::cout << cur->_data.first << ":" << cur->_data.second << "  ";
            cur = cur->_right;
        }
        std::cout << '\n';
	}

    void print_DLCR_rec() const noexcept {
        std::cout << "[In-order(rec):]\n";
        inorder(_root);
        std::cout << '\n';
    }
    
};