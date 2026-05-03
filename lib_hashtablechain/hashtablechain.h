#include <iostream>
#include <list>
#include <vector>
#include <string>

// ═══════════════════════════════════════════════════════════════════════════
//  Хеш-таблица методом цепочек
//
//  Каждая ячейка таблицы — это список (цепочка) пар ключ-значение.
//  При коллизии просто добавляем в конец списка.
//
//  [0] -> ...
//  [1] -> ...
//  [3] -> 10:ten -> 17:seventeen   // оба дали хеш 3
//  [6] -> 20:twenty
// ═══════════════════════════════════════════════════════════════════════════

template <typename TKey, typename TVal>
class HashChain {

    using Bucket = std::list<std::pair<TKey, TVal>>;

    std::vector<Bucket> _table;
    int _size;
    int _count = 0;

    int hash(const TKey& key) const {
        return key % _size;
    }

public:

    HashChain(int size = 11) : _size(size), _table(size) {}

    // ── insert ───────────────────────────────────────────────────────────────
    // Считаем хеш → идём в нужную цепочку → ищем ключ.
    // Если нашли — обновляем. Если нет — добавляем в конец.

    void insert(const TKey& key, const TVal& val) {
        int idx = hash(key);

        for (auto& pair : _table[idx]) {
            if (pair.first == key) {
                pair.second = val;
                return;
            }
        }

        _table[idx].push_back({ key, val });
        _count++;
    }

    // ── find ─────────────────────────────────────────────────────────────────
    // Считаем хеш → проходим по цепочке → ищем ключ.

    TVal* find(const TKey& key) {
        int idx = hash(key);

        for (auto& pair : _table[idx]) {
            if (pair.first == key)
                return &pair.second;
        }

        return nullptr;
    }

    // ── erase ────────────────────────────────────────────────────────────────
    // Считаем хеш → находим в цепочке → удаляем.

    bool erase(const TKey& key) {
        int idx = hash(key);
        Bucket& bucket = _table[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                _count--;
                return true;
            }
        }

        return false;
    }

    // ── print ─────────────────────────────────────────────────────────────────

    void print() const {
        for (int i = 0; i < _size; i++) {
            std::cout << '[' << i << ']';
            for (const auto& pair : _table[i])
                std::cout << " -> " << pair.first << ':' << pair.second;
            std::cout << '\n';
        }
        std::cout << "Элементов: " << _count << '\n';
    }
};

// ── main ─────────────────────────────────────────────────────────────────────

int main() {
    HashChain<int, std::string> table(7);

    std::cout << "=== insert: 10 20 17 3 1 ===\n";
    table.insert(10, "ten");
    table.insert(20, "twenty"); // 20 % 7 = 6
    table.insert(17, "seventeen"); // 17 % 7 = 3 — коллизия с 10!
    table.insert(3, "three");
    table.insert(1, "one");
    table.print();

    std::cout << "\nfind(17) = ";
    std::string* v = table.find(17);
    std::cout << (v ? *v : "not found") << '\n';

    std::cout << "\n=== erase(17) ===\n";
    table.erase(17);
    table.print();

    return 0;
}
