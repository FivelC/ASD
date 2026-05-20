#include <vector>
#include <string>
#include <type_traits>

template <typename TKey, typename TVal>
class BaseHash {
protected:
    size_t _capacity = 0;
    size_t _size = 0;

    bool isPrime(size_t n) const {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (size_t i = 3; i * i <= n; i += 2)
            if (n % i == 0) return false;
        return true;
    }

    size_t nextPrime(size_t n) const {
        while (!isPrime(n)) ++n;
        return n;
    }

    std::string toString(const TKey& key) const {
        if constexpr (std::is_same_v<TKey, std::string>)
            return key;
        else
            return std::to_string(key);
    }

    size_t hash1(const TKey& key) const {
        const std::string str = toString(key);
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); ++i)
            hash = hash * 33 + str[i];
        return hash % _capacity;
    }

    BaseHash(size_t capacity) {
        _capacity = nextPrime(capacity);
        _size = 0;
    }

public:
    size_t capacity() const { return _capacity; }
    size_t size() const { return _size; }

    virtual ~BaseHash() = default;
};