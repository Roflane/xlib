#pragma once
#include <functional>
#include <vector>

namespace xlib {

template <typename K, typename V>
struct Bucket {
    K key{};
    V value{};
    bool taken = false;
};

template <typename K, typename V>
class unordered_map {
    using bucket_t = Bucket<K, V>;
    using buckets_t = std::vector<bucket_t>;

private:
    buckets_t _buckets;
    size_t _size;
    size_t _cap;

    size_t hash(const K &key) const {
        std::hash<K> hasher;
        return hasher(key) % _cap;
    }

    size_t hash(const K &key, size_t cap) const {
        std::hash<K> hasher;
        return hasher(key) % cap;
    }

    void rehash() {
        size_t newCap = _cap * 2;
        buckets_t newBuckets(newCap);

        for (auto &bucket : _buckets) {
            if (!bucket.taken) continue;
            size_t index = hash(bucket.key, newCap);
            while (newBuckets[index].taken)
                index = (index + 1) % newCap;
            newBuckets[index] = bucket;
        }

        _buckets = std::move(newBuckets);
        _cap = newCap;
    }

public:
    class Iterator {
        bucket_t* _p;
        bucket_t* _end;
    public:
        Iterator(bucket_t* p, bucket_t* end) : _p(p), _end(end) {}

        bool operator!=(const Iterator &rhs) const {
            return _p != rhs._p;
        }

        V& operator*() const {
            return _p->value;
        }

        Iterator& operator++() {
            do ++_p;
            while (_p != _end && !_p->taken);
            return *this;
        }
    };

    explicit unordered_map(size_t cap = 8)
        : _buckets(cap), _size(0), _cap(cap) {}

    size_t size() const { return _size; }
    size_t cap() const { return _cap; }
    float load_factor() const { return static_cast<float>(_size) / _cap; }

    Iterator begin() {
        auto p = _buckets.data();
        auto end = p + _buckets.size();
        while (p != end && !p->taken) ++p;
        return Iterator(p, end);
    }

    Iterator end() {
        auto end = _buckets.data() + _buckets.size();
        return Iterator(end, end);
    }

    V& operator[](const K &key) {
        if (load_factor() >= 0.5f) rehash();
        size_t index = hash(key);
        while (_buckets[index].taken && _buckets[index].key != key)
            index = (index + 1) % _cap;

        if (!_buckets[index].taken) {
            _buckets[index].key = key;
            _buckets[index].value = {};
            _buckets[index].taken = true;
            ++_size;
        }

        return _buckets[index].value;
    }

    void insert(const K &key, const V &value) {
        if (load_factor() >= 0.5f) rehash();
        size_t index = hash(key);
        while (_buckets[index].taken && _buckets[index].key != key)
            index = (index + 1) % _cap;

        if (_buckets[index].taken)
            _buckets[index].value = value;
        else {
            _buckets[index].key = key;
            _buckets[index].value = value;
            _buckets[index].taken = true;
            ++_size;
        }
    }

    void erase(const K &key) {
        size_t index = hash(key);
        size_t start = index;

        // linear probing search
        while (_buckets[index].taken) {
            if (_buckets[index].key == key) {
                _buckets[index].taken = false;
                --_size;
                return;
            }
            index = (index + 1) % _cap;
            if (index == start) break; // full cycle
        }
    }
};

} // namespace xlib
