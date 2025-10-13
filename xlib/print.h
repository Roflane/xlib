#pragma once
#include <iostream>
#include <format>

namespace xlib {
    template<typename... VA>
    void println(const char* fmt, VA... args) {
        std::cout << std::vformat(fmt, std::make_format_args(args...));
    }
}