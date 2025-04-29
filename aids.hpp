#pragma once
#include <iostream>

template<typename... VA>
void prints(VA... va_args) {
    ((std::cout << va_args << ' '), ...);
}

template<typename... VA>
void printn(VA... va_args) {
    ((std::cout << va_args << '\n'), ...);
}


size_t strLen(const char *str) {
    size_t length = 0;

    while (*str) {
        length++;
        str++;
    }
    return length;
}


bool strCmp(const char *str, const char *str2) {
    for (size_t i = 0; str[i] != '\0' || str2[i] != '\0'; ++i) {
        if (str[i] != str2[i]) {
            return 1;
        }
    }
    return 0;
}


const char* strChr_s(const char *str, char chr) {
    size_t i = 0;
    for (; str[i] != '\0'; ++i) {
        if (*(str + i) == chr) {
            return &str[i];
        }
    }
    return &str[i]; // ret '\0'
}


const char* strChr(const char *str, char chr) {
    if (chr == '\0') return str + strLen(str);

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (*(str + i) == chr) {
            return &str[i];
        }
    }
    return nullptr;
}


const char* strStr(const char *str, const char *str2) {
    if (*str2 == '\0') return str;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (*(str + i) == *str2) {
            return &str[i];
        }
    }
    return nullptr;
}


const char* strCat(const char *str, const char *str2) {
    size_t length = strLen(str);
    size_t length2 = strLen(str2);
    size_t newSz = length + length2;
    char* newArr = new char[newSz + 1]();

    for (size_t i = 0; str[i] != '\0'; ++i) {
        newArr[i] = str[i];
    }

    for (size_t j = 0; str2[j] != '\0'; ++j) {
        newArr[j + length] = str2[j];
    }
    newArr[newSz] = '\0';

    return newArr;
}


const char* strCpy(char *buffer, const char *srcStr) {
    size_t i = 0;
    for (; srcStr[i] != '\0'; ++i) {
        *(buffer + i) = *(srcStr + i);
    }
    buffer[i] = '\0';

    return buffer;
}

void* __stdcall memCpy(void *dest, void *src, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        *(reinterpret_cast<unsigned char*>(dest) + i) = *(reinterpret_cast<unsigned char*>(src) + i);
    }
    return dest;
}

template <typename T>
T max(T value1, T value2) {
    return (value1 > value2) ? value1 : value2;
}

template <typename T>
T min(T value1, T value2) {
    return (value1 < value2) ? value1 : value2;
}

template <typename T>
T clamp(T trackValue, T minValue, T maxValue) {
    if (trackValue < minValue) { trackValue = minValue; }
    if (trackValue > maxValue) { trackValue = maxValue; }
    return trackValue;
}

template<typename T>
class XVec {
private:
    // Fields
    T* _data;
    size_t _size;
    size_t _cap;

    // Methods
    void resize() {
        size_t newCap = (_cap != 1) ? (_size * 1.5) : 2;
        T* newXVec = new T[newCap]();

        if (_size) {
            for (size_t i = 0; i < _size; ++i) {
                newXVec[i] = _data[i];
            }
        }
        delete[] _data;
        _data = newXVec;
        _cap = newCap;
    }
public:
    class Iterator {
    private:
        T* _current;
    public:
        Iterator(T* current) : _current(current) {}

        // Operator overloads
        bool operator!=(const Iterator& rhs) const {
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

    XVec() : _data(nullptr), _size(0), _cap(0) {}
    XVec(size_t size) : _size(size), _cap(size) {
        _data = (_cap > 0) ? new T[_cap]() : nullptr;
    }
    XVec(std::initializer_list<T> init_list) : _size(init_list.size()), _cap(init_list.size()) {
        _data = new T[_cap]();
        size_t index = 0;
        for (auto value : init_list) {
            if (index < _size) {
                _data[index++] = value;
            }
        }
    }
    XVec(const XVec& other) : _size(other._size), _cap(other._cap) {
        _data = new T[_cap]();
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    XVec(XVec&& other) noexcept : _data(other._data), _size(other._size), _cap(other._cap) {
        other._data = nullptr;
        other._size = 0;
        other._cap = 0;
    }
    ~XVec() {
        delete[] _data;
        _data = nullptr;
    }

    // Operator overloads
    XVec operator+(const XVec other) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (size_t i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] + other._data[i];
        }
        return newXVec;
    }

    XVec operator-(const XVec other) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (size_t i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] - other._data[i];
        }
        return newXVec;
    }

    XVec operator*(const XVec other) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (size_t i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] * other._data[i];
        }
        return newXVec;
    }

    XVec operator/(const XVec other) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);

        for (size_t i = 0; i < actualSize; ++i) {
            if (other._data[i] == 0) { return 0; }
            newXVec._data[i] = _data[i] / other._data[i];
        }
        return newXVec;
    }

    auto operator+=(const XVec other) -> decltype(_data) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;

        for (size_t i = 0; i < actualSize; ++i) {
            _data[i] += other._data[i];
        }
        return _data;
    }

    auto operator-=(const XVec other) -> decltype(_data) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;

        for (size_t i = 0; i < actualSize; ++i) {
            _data[i] -= other._data[i];
        }
        return _data;
    }

    auto operator*=(const XVec other) -> decltype(_data) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;

        for (size_t i = 0; i < actualSize; ++i) {
            _data[i] *= other._data[i];
        }
        return _data;
    }

    auto operator/=(const XVec other) -> decltype(_data) {
        size_t actualSize = (_size > other._size) ? other.size() : _size;

        for (size_t i = 0; i < actualSize; ++i) {
            _data[i] /= other._data[i];
        }
        return _data;
    }

    XVec& operator++() {
        for (size_t i = 0; i < _size; ++i) {
            ++_data[i];
        }
        return *this;
    }

    XVec operator++(int) {
        XVec temp(*this);
        for (size_t i = 0; i < _size; ++i) {
            ++_data[i];
        }
        return temp;
    }

    XVec& operator--() {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] -= 1;
        }
        return *this;
    }

    XVec operator--(int) {
        XVec temp = *this;
        --(*this);
        return temp;
    }

    T& operator[](size_t index) {
        if (index >= _size) { return _data[_size - 1]; }
        else if (index == _cap) { return _data[_size - 1]; }
        return _data[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const XVec& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            os << vec.get(i);
            if (i < vec.size() - 1) os << ", ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, XVec& vec) {
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

    // Methods
    Iterator begin() {
        return Iterator(_data);
    }

    Iterator end() {
        return Iterator(_data + _size);
    }

    size_t size() const { return _size; }
    size_t cap()  const { return _cap; }

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

    void remove(size_t index) {
        if (index >= _size - 1) { pop(); }

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

template<typename T>
class XStr {
private:
    char* _data;
    T _length;
public:
    XStr() : _data(nullptr), _length(0) {}
    XStr(const char* pStr) : _length(static_cast<T>(strLen(pStr))) {
        _data = new char[_length + 1];
        strcpy_s(_data, _length + 1, pStr);
    }
    XStr(const XStr& other) : _length(other._length) {
        _data = new char[_length + 1];
        strcpy_s(_data, _length + 1, other._data);
    }
    XStr(XStr &&other) noexcept : _data(other._data), _length(other._length) {
        other._data = nullptr;
        other._length = 0;
    }
    ~XStr() {
        for (size_t i = 0; i < _length; ++i) { _data[i] = 0x90; }
        delete[] _data;
        _data = nullptr;
    }

    // Operator overloads
    char operator[](T index) {
        return (index < _length) ? _data[index] : '\0';
    }

    void operator==(XStr &&other) {
        _data = new char[other._length + 1];
        strCpy(_data, sizeof(_data), other._data);
    }

    bool operator==(const char *other) const {
        return strCmp(_data, other) == 0;
    }

    XStr& operator=(const XStr &other) {
        if (this != &other) {
            delete[] _data;
            _length = other._length;
            _data = new char[_length + 1];
            strcpy_s(_data, other._data);
        }
        return *this;
    }

    XStr& operator=(XStr &&other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _length = other._length;
            other._data = nullptr;
            other._length = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const XStr& other) {
        os << other._data;
        return os;
    }

    // Properties
    T length() const { return _length; }
    const char* c_str() const { return _data; }

    // Methods
    void fragment() {
        for (T i = 0; i < _length; ++i) {
            T idx = rand() % _length;
            _data[idx] = 'A' + rand() % 26;
        }
    }

    void charSwap(char chr) {
        for (T i = 0; i < _length; ++i) {
            _data[i] = chr;
        }
    }
};


template<typename T>
struct Node {
    size_t id = 0;
    T value{};
    Node *next = nullptr;
    Node *prev = nullptr;
};

template<typename T>
class XLinkedList {
private:
    // Fields
    size_t _length;
    Node<T> *_pHead;
    Node<T> *_pTail;
public:
    class Iterator {
    public:
        Node<T> *current;
        Iterator(Node<T> *current) : current(current) {}

        // Operator overloads
        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }

        bool operator==(const Iterator &other) const {
            return current == other.current;
        }

        T& operator*() const {
            return current->value;
        }

        Iterator& operator++() {
            if (current != nullptr) { current = current->next; }
            return *this;
        }

        Iterator operator++(int) {
            auto temp = *this;
            if (current && current->next) current = current->next;
            return temp;
        }

        Iterator& operator--() {
            if (current && current->prev) current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            auto temp = current;
            if (current && current->prev) current = current->prev;
            return temp;
        }

        Iterator operator+(size_t inc) {
            auto temp = current;
            size_t i = 0;

            while (temp != nullptr && i < inc) {
                if (temp->next == nullptr) break;
                temp = temp->next;
                ++i;
            }
            return temp;
        }

        Iterator operator-(size_t dec) {
            auto temp = current;
            size_t i = 0;

            while (temp != nullptr && i < dec) {
                if (temp->prev == nullptr) break;
                temp = temp->prev;
                ++i;
            }
            return temp;
        }
    };

    XLinkedList() : _length(0), _pHead(nullptr), _pTail(nullptr) {}
    XLinkedList(const XLinkedList &other) : _length(other._length), _pHead(other._pHead), _pTail(other._pTail) {}
    explicit XLinkedList(XLinkedList &&other) noexcept {
        _length = other._length;
        _pHead = other._pHead;
        _pTail = other._pTail;
        other._length = 0;
        other._pHead = nullptr;
        other._pTail = nullptr;
    }
    ~XLinkedList() {
        Node<T> *current = _pHead;
        while (current != nullptr) {
            Node<T> *temp = current->next;
            delete current;
            current = temp;
        }
    }

    // Operator overloads
    bool operator!=(XLinkedList<T> &other) const {
        return _pHead != other._pHead;
    }

    XLinkedList<T> operator=(const XLinkedList<T> &other) {
        _length = other._length;
        _pHead = other._pHead;
        _pTail = other._pTail;
        return *this;
    }

    XLinkedList<T>& operator=(XLinkedList<T> &&other) noexcept {
        if (*this != other) {
            _length = other._length;
            _pHead = other._pHead;
            _pTail = other._pTail;
            other._length = 0;
            other._pHead = nullptr;
            other._pTail = nullptr;
        }
        return *this;
    }

    // Properties
    size_t size() const {
        return _length;
    }

    Iterator begin() {
        return static_cast<Iterator>(_pHead);
    }

    Iterator end() {
        return static_cast<Iterator>(nullptr);
    }

    // Methods
    Node<T>* push_back(const T &v) {
        Node<T> *newNode = new Node<T>;
        newNode->value = v;
        newNode->id = _length;

        if (_length == 0) {
            _pHead = _pTail = newNode;
        }
        else {
            _pTail->next = newNode;
            newNode->prev = _pTail;
            _pTail = newNode;
        }

        ++_length;
        return newNode;
    }

    void pop_front() {
        if (_pHead == nullptr) return;

        if (_pHead->next) {
            _pHead = _pHead->next;
            _pHead->prev = nullptr;
        }
        --_length;
    }

    void pop_back() {
        if (_pTail == nullptr) return;

        if (_pTail->prev) {
            _pTail = _pTail->prev;
            _pTail->next = nullptr;
        }
        --_length;
    }

    void clear() {
        Node<T> *current = _pHead;
        while (current != nullptr) {
            current->id = 0;
            current = current->next;
        }
        _pHead = nullptr;
        _pTail = nullptr;
        _length = 0;
    }

    bool empty() const {
        return (_length == 0) ? true : false;
    }

    void insert_after_id(const T &v, size_t id) {
        if (_length == 0 || id >= _length) {
            InsertAtEnd(v);
            return;
        }

        Node<T> *newNode = new Node<T>;
        newNode->value = v;
        newNode->id = _length;

        Node<T> *temp = _pHead;
        for (size_t i = 0; i < id; ++i) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        delete newNode;
        ++_length;
    }


    void remove(size_t id) {
        if (_pHead == nullptr || id >= _length) {
            return;
        }

        if (id == 0) {
            Node<T> *temp = _pHead;
            _pHead = _pHead->next;
            delete temp;
        }
        else {
            Node<T> *headNode = _pHead;
            for (size_t i = 0; i < id - 1; ++i) {
                headNode = headNode->next;
            }
            Node<T> *current = headNode->next;
            headNode->next = current->next;
            delete current;
        }
        --_length;
    }

    void reverse() {
        if (_length == 0 || !_pHead) return;

        Node<T> *current = _pHead;
        Node<T> *next = nullptr, *prev = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        _pHead = prev;
    }
};
