#pragma once

namespace xlib {
    template <typename T>
    void swap(T &first, T &second) noexcept {
        auto temp = first;
        first = second;
        second = temp;
    }

    template<typename T>
    void sort_bubble(T &collection, const size_t size) {
        if (&collection == nullptr || size <= 1) return;
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = 0; j < size - i - 1; j++) {
                swap(collection[j], collection[j + 1]);
            }
        }
    }

    template<typename T>
    void sort_selection(T &collection, const size_t size) {
        if (&collection == nullptr || size <= 1) return;
        for (size_t i = 0; i < size - 1; ++i) {
            size_t idx = i;

            for (size_t j = i + 1; j < size; ++j) {
                if (collection[j] < collection[idx]) {
                    idx = j;
                }
            }
            swap(collection[i], collection[idx]);
        }
    }

    template<typename T>
    void sort_insertion(T &collection, const size_t size) {
        if (&collection == nullptr || size <= 1) return;
        using ValueType = std::remove_reference_t<decltype(collection[0])>;

        for (int i = 1; i < size; ++i) {
            ValueType key = collection[i];
            int j = i - 1;

            while (j >= 0 && collection[j] > key) {
                collection[j + 1] = collection[j];
                j = j - 1;
            }
            collection[j + 1] = key;
        }
    }
}
