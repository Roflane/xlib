#pragma once
#include <type_traits>

namespace xlib {
    template <typename T>
    concept CTSmartPointer = !std::is_fundamental_v<T>;

    template <typename T>
    concept CTPointer = std::is_pointer_v<T>;
}