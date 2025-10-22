#pragma once
#include "../concepts.h"
#include "../semantics.h"

namespace xlib {
    struct ControlBlock {
        unsigned long long strongCount = 0;
        unsigned long long weakCount = 0;
        void *object = nullptr;
    };

    template <typename TConcept>
    class shared_ptr {
    private:
        TConcept *_object;
        ControlBlock *_cb;

        void copy(const shared_ptr &other) noexcept {
            _object = other._object;
            _cb = other._cb;
        }

        void move(shared_ptr &&other) noexcept {
            _object = xlib::move(other._object);
            _cb = other._cb;
            other._object = nullptr;
            other._cb = nullptr;
        }

        void destroy() {
            if (!_cb) return;
            if (_cb->strongCount > 0) --_cb->strongCount;

            if (_cb->strongCount == 0 && _object && _cb->object) {
                delete _object;
                _object = nullptr;
            }

            if (_cb && _cb->strongCount == 0 && _cb->weakCount == 0) {
                delete _cb;
                //if (_cb != nullptr) _cb = nullptr;
            }
        }

    public:
        shared_ptr() noexcept : _object(nullptr), _cb(nullptr) {}
        explicit shared_ptr(TConcept *object, ControlBlock *cb = new ControlBlock()) requires CTSmartPointer<TConcept>
            : _object(object), _cb(cb) { ++_cb->strongCount; }
        shared_ptr(const shared_ptr &other) {
            copy(other);
            if (_cb) ++_cb->strongCount;
        }
        shared_ptr(shared_ptr &&other) noexcept { move(other); }
        ~shared_ptr() { destroy(); }

        shared_ptr& operator=(const shared_ptr &other) noexcept {
            if (this != &other) {
                copy(other);
                destroy();
                if (_cb) ++_cb->strongCount;
            }
            return *this;
        }

        shared_ptr& operator=(shared_ptr &&other) noexcept {
            if (this != &other) move(other);
            return *this;
        }

        TConcept* operator->() noexcept { return _object; }
        const TConcept* operator->() const noexcept { return _object; }
        TConcept* operator*() noexcept { return *_object; }

        ControlBlock* get_block() const { return _cb; }
        TConcept* get() const noexcept { return _object; }
    };

    template <typename T, typename... Args>
    requires CTSmartPointer<T> && (CTSmartPointer<Args>&& ...)
    shared_ptr<T> make_shared(Args&&... args) {
        return shared_ptr<T>(new T(xlib::forward(args)...));
    }
}