#include <iostream>
#include <vector>
#include <string>

// ═══════════════════════════════════════════════════════════════════════════
//  Хеш-таблица с двойным хешированием (открытая адресация)
//
//  Все элементы хранятся прямо в массиве, списков нет.
//  При коллизии ищем следующую свободную ячейку по формуле:
//    idx = (h1(key) + i * h2(key)) % size,   i = 0, 1, 2, ...
//
//  Важно: размер таблицы должен быть простым числом,
//  а h2 никогда не должна возвращать 0 (иначе зациклимся на месте).
// ═══════════════════════════════════════════════════════════════════════════

template <typename TKey, typename TVal>
class HashDouble {

    enum class State { EMPTY, USED, DELETED };

    struct Cell {
        TKey  key;
        TVal  val;
        State state = State::EMPTY;
    };

    std::vector<Cell> _table;
    int _size;
    int _count = 0;

    // Первая хеш-функция — начальная позиция
    int h1(const TKey& key) const {
        return key % _size;
    }

    // Вторая хеш-функция — шаг при коллизии.
    // Формула 1 + key % (size-1) гарантирует результат от 1 до size-1.
    int h2(const TKey& key) const {
        return 1 + key % (_size - 1);
    }

public:

    HashDouble(int size = 11) : _size(size), _table(size) {}

    // ── insert ───────────────────────────────────────────────────────────────
    // Пробуем ячейки по формуле двойного хеширования пока не найдём свободную.

    bool insert(const TKey& key, const TVal& val) {
        if (_count >= _size) {
            std::cout << "Таблица заполнена!\n";
            return false;
        }

        int idx = h1(key);
        int step = h2(key);

        for (int i = 0; i < _size; i++) {
            Cell& cell = _table[idx];

            // Пустая или удалённая ячейка — вставляем
            if (cell.state == State::EMPTY || cell.state == State::DELETED) {
                cell.key = key;
                cell.val = val;
                cell.state = State::USED;
                _count++;
                return true;
            }

            // Ключ уже есть — обновляем значение
            if (cell.state == State::USED && cell.key == key) {
                cell.val = val;
                return true;
            }

            // Коллизия — делаем шаг по второй хеш-функции
            idx = (idx + step) % _size;
        }

        return false;
    }

    // ── find ─────────────────────────────────────────────────────────────────
    // Та же формула пробирования.
    // Останавливаемся если встретили EMPTY — дальше точно нет нужного ключа.
    // DELETED пропускаем и идём дальше.

    TVal* find(const TKey& key) {
        int idx = h1(key);
        int step = h2(key);

        for (int i = 0; i < _size; i++) {
            Cell& cell = _table[idx];

            if (cell.state == State::EMPTY)
                return nullptr;

            if (cell.state == State::USED && cell.key == key)
                return &cell.val;

            idx = (idx + step) % _size;
        }

        return nullptr;
    }

    // ── erase ────────────────────────────────────────────────────────────────
    // Не удаляем физически — помечаем как DELETED.
    // Если поставить EMPTY, то сломаем цепочки пробирования других ключей.

    bool erase(const TKey& key) {
        int idx = h1(key);
        int step = h2(key);

        for (int i = 0; i < _size; i++) {
            Cell& cell = _table[idx];

            if (cell.state == State::EMPTY)
                return false;

            if (cell.state == State::USED && cell.key == key) {
                cell.state = State::DELETED;
                _count--;
                return true;
            }

            idx = (idx + step) % _size;
        }

        return false;
    }

    // ── print ─────────────────────────────────────────────────────────────────

    void print() const {
        for (int i = 0; i < _size; i++) {
            std::cout << '[' << i << "] ";
            if (_table[i].state == State::EMPTY)   std::cout << "---";
            else if (_table[i].state == State::DELETED) std::cout << "DEL";
            else std::cout << _table[i].key << ':' << _table[i].val;
            std::cout << '\n';
        }
        std::cout << "Элементов: " << _count << '\n';
    }
};

// ── main ─────────────────────────────────────────────────────────────────────

int main() {
    HashDouble<int, std::string> table(11);

    std::cout << "=== insert: 10 21 32 5 16 ===\n";
    table.insert(10, "ten");
    table.insert(21, "twenty-one"); // 21 % 11 = 10 — коллизия с 10!
    table.insert(32, "thirty-two"); // 32 % 11 = 10 — снова коллизия!
    table.insert(5, "five");
    table.insert(16, "sixteen");
    table.print();

    std::cout << "\nfind(32) = ";
    std::string* v = table.find(32);
    std::cout << (v ? *v : "not found") << '\n';

    std::cout << "\n=== erase(21) ===\n";
    table.erase(21);
    table.print();

    // Проверяем что find(32) работает после удаления соседа
    std::cout << "\nfind(32) после удаления 21 = ";
    v = table.find(32);
    std::cout << (v ? *v : "not found") << '\n';

    return 0;
}