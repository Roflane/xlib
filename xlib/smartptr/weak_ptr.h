#pragma once
#include "shared_ptr.h"

namespace xlib {
    template <typename T>
    class weak_ptr {
    private:
        ControlBlock *_cb;
    public:
        weak_ptr() : _cb(nullptr) {}
        weak_ptr(shared_ptr<T> shared_ptr) : _cb(shared_ptr.get_block()) { ++_cb->weakCount; }
        weak_ptr(const weak_ptr &other) : _cb(other._cb) { ++_cb->weakCount; }
        weak_ptr(weak_ptr &&other) noexcept : _cb(xlib::move(other._cb)) {}
        ~weak_ptr() {
            if (_cb) {
                --_cb->weakCount;
                if (_cb->strongCount == 0 && _cb->weakCount == 0)
                    delete _cb;
            }
        }

        weak_ptr& operator=(const weak_ptr &other) {
            if (this != &other) _cb = other._cb;
            return *this;
        }

        weak_ptr& operator=(weak_ptr &&other) noexcept {
            if (this != &other) _cb = xlib::move(other._cb);
            return *this;
        }

        shared_ptr<T> lock() const noexcept {
            if (!_cb || _cb->strongCount == 0) return shared_ptr<T>();
            ++_cb->strongCount;
            return shared_ptr<T>(_cb->object, _cb);
        }

        bool expired() const {
            return !_cb || _cb->strongCount == 0;
        }
    };
}
