#pragma once
#include <cstdint>
#include <immintrin.h>
#include "Context/XlibContext.h"

namespace xlib::intrinsics {
    inline uint64_t _rdtsc_() { return __rdtsc(); }

    template<typename T>
    static auto _rdrand() -> T {
        static_assert(sizeof(T) == 0, "Unsupported type for _rdrand");
        return T{};
    }

    template <>
    inline auto _rdrand<uint64_t>() -> uint64_t {
        uint64_t result = 0;
        if (xlib_context.getRdrandSupported()) return result;

#ifdef __GNUC__
        __asm__ __volatile__(
            "rdrand %0"
            : "=r"(result)
        );
#else
        _rdrand64_step(&result);
#endif
        return result;
    }

    template <>
    inline auto _rdrand<uint32_t>() -> uint32_t {
        uint32_t result = 0;
        if (!xlib_context.getRdrandSupported()) return result;

#ifdef __GNUC__
        __asm__ __volatile__(
            "rdrand %0"
            : "=a"(result)
        );
#else
        _rdrand32_step(&result);
#endif
        return result;
    }

    template <>
    inline auto _rdrand<uint16_t>() -> uint16_t {
        uint16_t result = 0;
        if (!xlib_context.getRdrandSupported()) return result;

#ifdef __GNUC__
        __asm__ __volatile__(
            "rdrand %0"
            : "=a"(result)
        );
#else
        _rdrand16_step(&result);
#endif
        return result;
    }

    template <>
    inline auto _rdrand<uint8_t>() -> uint8_t {
        uint8_t result = 0;
        if (!xlib_context.getRdrandSupported()) return result;

#ifdef __GNUC__
        result = _rdrand<uint16_t>();
#else
        _rdrand16_step(reinterpret_cast<uint16_t*>(&result));
#endif
        return result;
    }

    template<typename T>
    static auto _rdseed() -> T {
        static_assert(sizeof(T) == 0, "Unsupported type for _rdseed");
        return T{};
    }

    template <>
    inline auto _rdseed<uint64_t>() -> uint64_t {
        uint64_t result = 0;
        if (!xlib_context.getRdseedSupported()) return result;

#ifdef __GNUC__
        unsigned char status;
        __asm__ (
            "rdseed %0"
            : "=r"(result)
        );
#else
        _rdseed64_step(&result);
#endif
        return result;
    }

    template <>
    inline auto _rdseed<uint32_t>() -> uint32_t {
        uint32_t result = 0;
        if (!xlib_context.getRdseedSupported()) return result;

#ifdef __GNUC__
        __asm__ (
            "rdseed %0"
            : "=a"(result)
        );
#else
        _rdseed32_step(&result);
#endif
        return result;
    }

    template <>
    inline auto _rdseed<uint16_t>() -> uint16_t {
        uint16_t result = 0;
        if (!xlib_context.getRdseedSupported()) return result;

#ifdef __GNUC__
        __asm__ (
            "rdseed %0"
            : "=a"(result)
        );
#else
        _rdseed16_step(&result);
#endif
        return result;
    }
}