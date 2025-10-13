#pragma once

namespace xlib {
    template <typename T>
    T max(T value1, T value2) {
        return value1 > value2 ? value1 : value2;
    }

    template <typename T>
    T min(T value1, T value2) {
        return value1 < value2 ? value1 : value2;
    }

    template <typename T>
    T clamp(T trackValue, T minValue, T maxValue) {
        if (trackValue < minValue) { trackValue = minValue; }
        if (trackValue > maxValue) { trackValue = maxValue; }
        return trackValue;
    }

    template <typename T>
    T factorial(T n) {
        if (n == 0) return 1;
        return n * factorial(n - 1);
    }
}
