#include <iostream>
#include <queue>
#include <algorithm> // std::max

// ═══════════════════════════════════════════════════════════════════════════
//  AVL-дерево
//
//  Это то же BST, но после каждой вставки/удаления
//  дерево само себя балансирует через повороты.
//
//  Баланс узла = высота правого поддерева - высота левого.
//  Допустимые значения: -1, 0, 1.
//  Если баланс стал -2 или 2 — делаем поворот.
// ═══════════════════════════════════════════════════════════════════════════

template <typename TKey, typename TVal>
class AVLTree {

    struct Node {
        std::pair<TKey, TVal> _data;
        Node* _left = nullptr;
        Node* _right = nullptr;
        int   _height = 1; // высота поддерева с корнем в этом узле

        Node(const TKey& k, const TVal& v) : _data(k, v) {}
    };

    Node* _root = nullptr;

public:

    AVLTree() = default;

    ~AVLTree() { clear(_root); }

    bool isEmpty() const noexcept { return _root == nullptr; }

    // ── insert ───────────────────────────────────────────────────────────────

    void insert(const TKey& key, const TVal& val) {
        _root = insertNode(_root, key, val);
    }

    // ── find ─────────────────────────────────────────────────────────────────
    // Обычный BST-поиск, AVL не меняет порядок ключей

    TVal* find(const TKey& key) const noexcept {
        Node* cur = _root;
        while (cur) {
            if (key == cur->_data.first) return &cur->_data.second;
            else if (key < cur->_data.first) cur = cur->_left;
            else                              cur = cur->_right;
        }
        return nullptr;
    }

    // ── erase ────────────────────────────────────────────────────────────────

    void erase(const TKey& key) {
        _root = eraseNode(_root, key);
    }

    // ── print_tree (BFS по уровням) ──────────────────────────────────────────

    void print_tree() const noexcept {
        if (!_root) { std::cout << "(empty)\n"; return; }

        std::queue<Node*> q;
        q.push(_root);

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                Node* cur = q.front(); q.pop();
                std::cout << cur->_data.first << ' ';
                if (cur->_left)  q.push(cur->_left);
                if (cur->_right) q.push(cur->_right);
            }
            std::cout << '\n';
        }
    }

    // ── print_ordered (in-order = по возрастанию) ────────────────────────────

    void print_ordered() const noexcept {
        inorder(_root);
        std::cout << '\n';
    }

private:

    // ── Вспомогательные функции для высоты и баланса ─────────────────────────

    int height(Node* n) const {
        return n ? n->_height : 0;
    }

    void updateHeight(Node* n) {
        n->_height = 1 + std::max(height(n->_left), height(n->_right));
    }

    // Баланс = высота правого - высота левого
    // -2: перевес влево  → нужен правый поворот
    // +2: перевес вправо → нужен левый поворот
    int balance(Node* n) const {
        return n ? height(n->_right) - height(n->_left) : 0;
    }

    // ── Повороты ─────────────────────────────────────────────────────────────
    //
    // Правый поворот (когда баланс = -2, дерево "упало" влево):
    //
    //      n              l
    //     / \            / \
    //    l   C    →     A   n
    //   / \                / \
    //  A   B              B   C
    //
    Node* rotateRight(Node* n) {
        Node* l = n->_left;
        Node* B = l->_right;

        l->_right = n;
        n->_left = B;

        updateHeight(n); // сначала n, потом l — n теперь ниже
        updateHeight(l);

        return l; // l становится новым корнем
    }

    // Левый поворот (когда баланс = +2, дерево "упало" вправо):
    //
    //    n                r
    //   / \              / \
    //  A   r      →     n   C
    //     / \          / \
    //    B   C        A   B
    //
    Node* rotateLeft(Node* n) {
        Node* r = n->_right;
        Node* B = r->_left;

        r->_left = n;
        n->_right = B;

        updateHeight(n);
        updateHeight(r);

        return r; // r становится новым корнем
    }

    // ── Балансировка узла ─────────────────────────────────────────────────────
    //
    // Вызывается после вставки/удаления.
    // Проверяем баланс и делаем нужный поворот.
    //
    // 4 случая:
    //
    // 1. Левый-левый (баланс = -2, левый ребёнок тоже влево):
    //       один правый поворот
    //
    // 2. Левый-правый (баланс = -2, левый ребёнок вправо):
    //       сначала левый поворот левого ребёнка,
    //       потом правый поворот узла
    //
    // 3. Правый-правый (баланс = +2, правый ребёнок тоже вправо):
    //       один левый поворот
    //
    // 4. Правый-левый (баланс = +2, правый ребёнок влево):
    //       сначала правый поворот правого ребёнка,
    //       потом левый поворот узла

    Node* rebalance(Node* n) {
        updateHeight(n);
        int b = balance(n);

        // Случай 1: левый-левый
        if (b == -2 && balance(n->_left) <= 0)
            return rotateRight(n);

        // Случай 2: левый-правый
        if (b == -2 && balance(n->_left) > 0) {
            n->_left = rotateLeft(n->_left);
            return rotateRight(n);
        }

        // Случай 3: правый-правый
        if (b == 2 && balance(n->_right) >= 0)
            return rotateLeft(n);

        // Случай 4: правый-левый
        if (b == 2 && balance(n->_right) < 0) {
            n->_right = rotateRight(n->_right);
            return rotateLeft(n);
        }

        return n; // баланс в норме, ничего не делаем
    }

    // ── Рекурсивная вставка ───────────────────────────────────────────────────
    // Вставляем как в обычное BST, потом на обратном пути (возврат из рекурсии)
    // пересчитываем высоты и балансируем.

    Node* insertNode(Node* n, const TKey& key, const TVal& val) {
        if (!n) return new Node(key, val);

        if (key == n->_data.first) {
            n->_data.second = val; // обновляем значение
            return n;
        }
        else if (key < n->_data.first) {
            n->_left = insertNode(n->_left, key, val);
        }
        else {
            n->_right = insertNode(n->_right, key, val);
        }

        return rebalance(n);
    }

    // ── Рекурсивное удаление ──────────────────────────────────────────────────
    // Как в BST: при двух потомках берём максимум левого поддерева.
    // После — балансируем на обратном пути.

    Node* eraseNode(Node* n, const TKey& key) {
        if (!n) return nullptr;

        if (key < n->_data.first) {
            n->_left = eraseNode(n->_left, key);
        }
        else if (key > n->_data.first) {
            n->_right = eraseNode(n->_right, key);
        }
        else {
            // Нашли узел

            // Нет потомков или один потомок
            if (!n->_left || !n->_right) {
                Node* child = n->_left ? n->_left : n->_right;
                delete n;
                return child; // может быть nullptr
            }

            // Два потомка: берём максимум левого поддерева
            Node* maxLeft = n->_left;
            while (maxLeft->_right)
                maxLeft = maxLeft->_right;

            n->_data = maxLeft->_data;
            n->_left = eraseNode(n->_left, maxLeft->_data.first);
        }

        return rebalance(n);
    }

    void inorder(Node* n) const noexcept {
        if (!n) return;
        inorder(n->_left);
        std::cout << n->_data.first << ':' << n->_data.second << "  ";
        inorder(n->_right);
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->_left);
        clear(n->_right);
        delete n;
    }
};

// ── main ─────────────────────────────────────────────────────────────────────

int main() {
    AVLTree<int, std::string> tree;

    // Вставляем по возрастанию — обычное BST стало бы "палкой",
    // AVL будет балансироваться автоматически
    std::cout << "=== insert: 1 2 3 4 5 6 7 ===\n";
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three"); // здесь сработает левый поворот
    tree.insert(4, "four");
    tree.insert(5, "five");  // снова поворот
    tree.insert(6, "six");
    tree.insert(7, "seven");
    tree.print_tree();       // должно быть сбалансированное дерево, не палка

    std::cout << "\n=== упорядоченный вывод ===\n";
    tree.print_ordered();

    std::cout << "\n=== find(5) = ";
    std::string* v = tree.find(5);
    std::cout << (v ? *v : "not found") << '\n';

    std::cout << "\n=== erase(4) ===\n";
    tree.erase(4);
    tree.print_tree();

    std::cout << "\n=== erase(2) ===\n";
    tree.erase(2);
    tree.print_tree();

    std::cout << "\n=== упорядоченный вывод после удалений ===\n";
    tree.print_ordered();

    return 0;
}