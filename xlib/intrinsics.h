#pragma once
#include <cstdint>
#include <immintrin.h>

namespace xlib::intrinsics {
    inline bool _supports_rdrand() {
        unsigned eax = 0;
#ifdef __GNUC__
        __asm__ __volatile__ (
            "mov $1, %%eax\n\t"
            "cpuid\n\t"
            "mov %%ecx, %%eax\n\t"
            "shl $30, %%edx\n\t"
            "and %%edx, %%eax\n\t"
            "shr $30, %%eax\n\t"
            : "=a" (eax)
            :
            : "ebx", "ecx", "edx"
        );
#endif
        return eax;
    }

    inline bool _supports_rdseed() {
        unsigned eax;
#ifdef __GNUC__
        __asm__ __volatile__ (
            "mov $7, %%eax\n\t"
            "xor %%ecx, %%ecx\n\t"
            "cpuid\n\t"
            "bt $18, %%ebx\n\t"
            "setc %%al\n\t"
            "movzx %%al, %%eax\n\t"
            : "=a" (eax)
            :
            : "ebx", "ecx", "edx"
        );
#endif
        return eax;
    }

    inline uint64_t _rdtsc_() {
        return __rdtsc();
    }


    template<typename T>
    static auto _rdrand() -> T {
        static_assert(sizeof(T) == 0, "Unsupported type for _rdrand");
        return T{};
    }

    template <>
    inline auto _rdrand<uint64_t>() -> uint64_t {
        uint64_t result = 0;
        if (!_supports_rdrand()) return result;

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
        if (!_supports_rdrand()) return result;

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
        if (!_supports_rdrand()) return result;

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

    template<typename T>
    static auto _rdseed() -> T {
        static_assert(sizeof(T) == 0, "Unsupported type for _rdseed");
        return T{};
    }

    template <>
    inline auto _rdseed<uint64_t>() -> uint64_t {
        uint64_t result = 0;
        if (!_supports_rdseed()) return result;

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
        if (!_supports_rdseed()) return result;

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
        if (!_supports_rdseed()) return result;

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