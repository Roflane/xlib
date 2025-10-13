#pragma once

namespace xlib {
    inline size_t strlen(const char *str) {
        size_t length = 0;

        while (*str) {
            length++;
            str++;
        }
        return length;
    }


    inline bool strcmp(const char *str, const char *str2) {
        for (size_t i = 0; str[i] != '\0' || str2[i] != '\0'; ++i) {
            if (str[i] != str2[i]) {
                return true;
            }
        }
        return false;
    }


    inline const char* strchr_s(const char *str, const char chr) {
        size_t i = 0;
        for (; str[i] != '\0'; ++i) {
            if (*(str + i) == chr) {
                return &str[i];
            }
        }
        return &str[i]; // ret '\0'
    }


    inline const char* strchr(const char *str, const char chr) {
        if (chr == '\0') return str + strlen(str);

        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (*(str + i) == chr) {
                return &str[i];
            }
        }
        return nullptr;
    }


    inline const char* strstr(const char *str, const char *str2) {
        if (*str2 == '\0') return str;

        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (*(str + i) == *str2) {
                return &str[i];
            }
        }
        return nullptr;
    }


    inline const char* strCat(const char *str, const char *str2) {
        const size_t length = strlen(str);
        const size_t length2 = strlen(str2);
        const size_t newSz = length + length2;
        char* newArr = new char[newSz + 1]();

        for (size_t i = 0; str[i] != '\0'; ++i) {
            newArr[i] = str[i];
        }
        for (size_t j = 0; str2[j] != '\0'; ++j) {
            newArr[j + length] = str2[j];
        }
        newArr[newSz] = '\0';

        return newArr;
    }


    inline const char* strcpy(char *buffer, const char *srcStr) {
        size_t i = 0;
        for (; srcStr[i] != '\0'; ++i) {
            *(buffer + i) = *(srcStr + i);
        }
        buffer[i] = '\0';
        return buffer;
    }

    template <typename T>
    T* memcpy(void *dest, const void *src, const size_t size) {
        for (size_t i = 0; i < size; ++i) {
            *(static_cast<T*>(dest) + i) = *(static_cast<T*>(src) + i);
        }
        return dest;
    }

    template <typename T>
    T* memset(T *dest, unsigned char c, const size_t count) {
        T* newDest = dest;
        for (size_t i = 0; i < count; ++i) {
            newDest[i] = c;
        }
        return newDest;
    }
}