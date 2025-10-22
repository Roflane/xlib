#pragma once
#include <initializer_list>
#include <iosfwd>

namespace xlib {
    template<typename T>
    class vector {
    private:
        T* _data;
        size_t _size;
        size_t _cap;
        
        void resize() {
            const size_t newCap = _cap != 1 ? _size * 1.5 : 2;
            T* newVector = new T[newCap]();

            if (_size) {
                for (size_t i = 0; i < _size; ++i) {
                    newVector[i] = _data[i];
                }
            }
            delete[] _data;
            _data = newVector;
            _cap = newCap;
        }
    public:
        class Iterator {
        private:
            T* _current;
        public:
            explicit Iterator(T* current) : _current(current) {}
            
            bool operator!=(const Iterator &rhs) const {
                return _current != rhs._current;
            }

            T& operator*() const {
                return *_current;
            }

            Iterator& operator++() {
                ++_current;
                return *this;
            }
        };

        vector() : _data(nullptr), _size(0), _cap(0) {}
        explicit vector(const size_t size) : _size(size), _cap(size) {
            _data = _cap > 0 ? new T[_cap]() : nullptr;
        }
        vector(std::initializer_list<T> init_list) : _size(init_list.size()), _cap(init_list.size()) {
            _data = new T[_cap]();
            size_t index = 0;
            for (auto value : init_list) {
                if (index < _size) {
                    _data[index++] = value;
                }
            }
        }
        vector(const vector &other) : _size(other._size), _cap(other._cap) {
            _data = new T[_cap]();
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        vector(vector &&other) noexcept : _data(other._data), _size(other._size), _cap(other._cap) {
            other._data = nullptr;
            other._size = 0;
            other._cap = 0;
        }
        ~vector() {
            println("~vector()");
            delete[] _data;
            _data = nullptr;
        }

        vector& operator=(const vector& other) {
            if (this != & other) {
                _size = other._size;
                _cap = other._cap;
                _data = new T[_cap]();
                for (size_t i = 0; i < _size; ++i) {
                    _data[i] = other._data[i];
                }
            }
            return *this;
        }

        vector& operator=(vector&& other) noexcept {
            if (this != &other) {
                delete[] _data;
                _data = nullptr;

                _size = other._size;
                _cap = other._cap;
                _data = other._data;

                other._data = nullptr;
                other._size = 0;
                other._cap = 0;

            }
            return *this;
        }

        vector operator+(const vector other) {
            size_t actualSize = _size > other._size ? other.size() : _size;
            vector newVector(actualSize);
            for (size_t i = 0; i < actualSize; ++i) {
                newVector._data[i] = _data[i] + other._data[i];
            }
            return newVector;
        }

        vector operator-(const vector other) {
            const size_t actualSize = _size > other._size ? other.size() : _size;
            vector newVector(actualSize);
            for (size_t i = 0; i < actualSize; ++i) {
                newVector._data[i] = _data[i] - other._data[i];
            }
            return newVector;
        }

        vector operator*(const vector other) {
            const size_t actualSize = _size > other._size ? other.size() : _size;
            vector newVector(actualSize);
            for (size_t i = 0; i < actualSize; ++i) {
                newVector._data[i] = _data[i] * other._data[i];
            }
            return newVector;
        }

        vector operator/(const vector other) {
            size_t actualSize = _size > other._size ? other.size() : _size;
            vector newVector(actualSize);

            for (size_t i = 0; i < actualSize; ++i) {
                if (other._data[i] == 0) { return 0; }
                newVector._data[i] = _data[i] / other._data[i];
            }
            return newVector;
        }

        auto operator+=(const vector other) -> decltype(_data) {
            const size_t actualSize = _size > other._size ? other.size() : _size;

            for (size_t i = 0; i < actualSize; ++i) {
                _data[i] += other._data[i];
            }
            return _data;
        }

        auto operator-=(const vector other) -> decltype(_data) {
            const size_t actualSize = _size > other._size ? other.size() : _size;

            for (size_t i = 0; i < actualSize; ++i) {
                _data[i] -= other._data[i];
            }
            return _data;
        }

        auto operator*=(const vector other) -> decltype(_data) {
            const size_t actualSize = _size > other._size ? other.size() : _size;

            for (size_t i = 0; i < actualSize; ++i) {
                _data[i] *= other._data[i];
            }
            return _data;
        }

        auto operator/=(const vector other) -> decltype(_data) {
            const size_t actualSize = _size > other._size ? other.size() : _size;

            for (size_t i = 0; i < actualSize; ++i) {
                _data[i] /= other._data[i];
            }
            return _data;
        }

        vector& operator++() {
            for (size_t i = 0; i < _size; ++i) {
                ++_data[i];
            }
            return *this;
        }

        vector operator++(int) {
            vector temp(*this);
            for (size_t i = 0; i < _size; ++i) {
                ++_data[i];
            }
            return temp;
        }

        vector& operator--() {
            for (size_t i = 0; i < _size; ++i) {
                _data[i] -= 1;
            }
            return *this;
        }

        vector operator--(int) {
            vector temp = *this;
            --*this;
            return temp;
        }

        T& operator[](size_t index) {
            if (index >= _size) throw std::out_of_range("Index is out of range");
            return _data[index];
        }

        const T& operator[](size_t index) const {
            if (index >= _size) throw std::out_of_range("Index is out of range");
            return _data[index];
        }

        friend std::ostream& operator<<(std::ostream& os, const vector& vec) {
            for (size_t i = 0; i < vec.size(); ++i) {
                os << vec.get(i);
                if (i < vec.size() - 1) os << ", ";
            }
            return os;
        }

        friend std::istream& operator>>(std::istream& is, vector& vec) {
            for (size_t i = 0; i < vec.size(); ++i) {
                is >> vec._data[i];
            }
            return is;
        }

        // Properties
        T get(size_t index) const {
            if (index >= _size) { return T(); }
            return _data[index];
        }

        void set(T value, size_t index) {
            if (index >= _size) {
                push_back(value);
            }
            _data[index] = value;
        }

        T* data() { return _data; }
        const T* data() const { return _data; }

        // Methods
        Iterator begin() {
            return Iterator(_data);
        }

        Iterator end() {
            return Iterator(_data + _size);
        }

        [[nodiscard]] size_t size() const { return _size; }
        [[nodiscard]] size_t cap()  const { return _cap; }

        void push_back(T value) {
            if (_size == _cap) { resize(); }
            _data[_size++] = value;
        }

        void insert(T value, size_t index) {
            if (_size == _cap) { resize(); }
            if (index > _size) { index = _size; }

            for (size_t i = _size; i > index; --i) {
                _data[i] = _data[i - 1];
            }
            _data[index] = value;
            _size++;
        }

        void remove(const size_t index) {
            if (index >= _size - 1) return;

            for (size_t i = index; i < _size - 1; ++i) {
                _data[i] = _data[i + 1];
            }
            _size--;
        }

        void remove(const Iterator it) {
            if (it == end()) return;

            const size_t index = it._current - _data;
            for (size_t i = index; i < _size - 1; ++i) {
                _data[i] = _data[i + 1];
            }
            _size--;
        }

        void pop() {
            if (_size == 0) return;
            _size -= 1;
        }
    };
}