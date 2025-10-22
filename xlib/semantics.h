#pragma once
#include <type_traits>

namespace xlib {
    template <typename T>
    constexpr T&& forward(T &object) noexcept {
        return static_cast<T&&>(object);
    }

    template <typename T>
    constexpr std::remove_reference_t<T>&& move(T &object) {
        return static_cast<std::remove_reference_t<T>&&>(object);
    }
}