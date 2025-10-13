#pragma once
#include <cstdint>
#include <iosfwd>
#include "string.h"

namespace xlib {
    class string {
    private:
        char* _data;
        size_t _length;
        size_t _cap;
        
        void resize() {
            const size_t newCap = _cap != 1 ? _length * 1.5 : 2;
            char* newString = new char[newCap]();

            if (_length) {
                for (size_t i = 0; i < _length; ++i) {
                    newString[i] = _data[i];
                }
            }
            delete[] _data;
            _data = newString;
            _cap = newCap;
        }
    public:
        class Iterator {
        private:
            char* _current;
        public:
            explicit Iterator(char* current) : _current(current) {}
            
            bool operator!=(const Iterator& rhs) const {
                return _current != rhs._current;
            }

            char& operator*() const {
                return *_current;
            }

            Iterator& operator++() {
                ++_current;
                return *this;
            }
        };

        string() : _data(nullptr), _length(0), _cap(sizeof(void*)) {}
        explicit string(const char *str) {
            _length = strlen(str) + 1;
            _cap = _length;
            _data = new char[_length];
            strcpy(_data, str);
        }
        string(const string& other) : _length(other._length), _cap(other._cap) {
            _data = new char[_cap]();
            strcpy(_data, other._data);
        }
        string(string&& other) noexcept : _data(other._data), _length(other._length), _cap(other._cap) {
            other._data = nullptr;
            other._length = 0;
            other._cap = 0;
        }
        ~string() {
            delete[] _data;
            _data = nullptr;
        }

        string& operator=(const string &other) {
            if (this != &other) {
                delete[] _data;
                _length = other._length;
                _data = new char[_length + 1];
                strcpy(_data, other._data);
            }
            return *this;
        }

        string& operator=(const char *str) {
            delete[] _data;
            _length = strlen(str) + 1;
            _cap = _length;
            _data = new char[_length + 1];
            strcpy(_data, str);
            return *this;
        }

        string& operator=(string &&other) noexcept {
            if (this != &other) {
                delete[] _data;
                _data = other._data;
                _length = other._length;
                other._data = nullptr;
                other._length = 0;
            }
            return *this;
        }

        char& operator[](const size_t index) const {
            if (index >= _length) { return _data[_length - 1]; }
            if (index == _cap)  { return _data[_length - 1]; }
            return _data[index];
        }

        friend std::ostream& operator<<(std::ostream& os, const string& vec) {
            for (size_t i = 0; i < vec.size(); ++i) {
                os << vec._data[i];
            }
            return os;
        }

        friend std::istream& operator>>(std::istream& is, string& vec) {
            for (size_t i = 0; i < vec.size(); ++i) {
                is >> vec._data[i];
            }
            return is;
        }

        // Properties
        [[nodiscard]] size_t length() const       { return _length; }
        [[nodiscard]] size_t capacity() const     { return _cap; }
        [[nodiscard]] const char* c_str() const   { return _data; }

        // Methods
        [[nodiscard]] Iterator begin() const { return Iterator(_data); }

        [[nodiscard]] Iterator end() const;

        [[nodiscard]] size_t size() const { return _length; }
        [[nodiscard]] size_t cap()  const { return _cap; }

        void push_back(char value) {
            if (_length == _cap) { resize(); }
            _data[_length++] = value;
        }

        void insert(char value, size_t index) {
            if (_length == _cap) { resize(); }
            if (index > _length) { index = _length; }

            for (size_t i = _length; i > index; --i) {
                _data[i] = _data[i - 1];
            }
            _data[index] = value;
            _length++;
        }

        void remove(const size_t index) {
            if (index >= _length - 1) { pop(); }

            for (size_t i = index; i < _length - 1; ++i) {
                _data[i] = _data[i + 1];
            }
            _length--;
        }

        void pop() {
            if (_length == 0) return;
            _length -= 1;
        }
    };

    inline string::Iterator string::end() const {
        return Iterator(_data + _length);
    }
}
