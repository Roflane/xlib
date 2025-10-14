#pragma once
#include <iostream>
#include <format>

namespace xlib {
    template<typename... Args>
    void println(const char* fmt, Args&&... args) {
        std::cout << std::vformat(fmt, std::make_format_args(args...)) << '\n';
    }
}