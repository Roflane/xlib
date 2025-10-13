#pragma once
#include <cstdint>

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
            if (current != nullptr) current = current->next;
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

        Iterator operator+(const size_t inc) {
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

    size_t size() const {
        return _length;
    }

    Iterator begin() {
        return static_cast<Iterator>(_pHead);
    }

    Iterator end() {
        return static_cast<Iterator>(nullptr);
    }

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
        return _length == 0;
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
            const Node<T> *temp = _pHead;
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