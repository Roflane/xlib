#pragma once
#include "../concepts.h"
#include "../algorithm.h"
#include "../semantics.h"

namespace xlib {
    template <typename TConcept>
    class unique_ptr {
    private:
        TConcept *_object;
    public:
        explicit unique_ptr(TConcept *object) requires CTSmartPointer<TConcept>
            : _object(object) {}
        unique_ptr(const unique_ptr &other) = delete;
        unique_ptr(unique_ptr &&other) = delete;
        ~unique_ptr() { delete _object; }

        unique_ptr& operator=(const unique_ptr &other) = delete;
        unique_ptr& operator=(unique_ptr &&other) = delete;
        TConcept* operator->() noexcept { return _object; }
        const TConcept* operator->() const noexcept { return _object; }
        TConcept* operator*() noexcept { return *_object; }

        TConcept* get() const noexcept { return _object; }
        constexpr void swap(unique_ptr &other) noexcept { xlib::swap(_object, other._object); }

        constexpr TConcept* release() noexcept {
            TConcept *p = _object;
            _object = nullptr;
            return p;
        }

        template <typename T> requires CTPointer<T>
        constexpr void reset(T pointer) noexcept {
            if (_object != pointer) {
                delete _object;
                _object = pointer;
            }
        }

        constexpr void reset() noexcept {
            if (_object) {
                delete _object;
                _object = nullptr;
            }
        }
    };

    template <typename T, typename... Args>
    requires CTSmartPointer<T> && (CTSmartPointer<Args>&& ...)
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(xlib::forward(args)...));
    }
}

