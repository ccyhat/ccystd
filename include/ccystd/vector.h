#pragma once

#include <cstddef>
#include <type_traits>
#include "ccystd/iterator.h"

namespace ccystd {

// --- vector ---
template <class T>
class vector {
public:
    using iterator       = T*;
    using const_iterator = const T*;
    using reverse_iterator       = reverse_iterator_t<T*>;
    using const_reverse_iterator = reverse_iterator_t<const T*>;

    // --- Construction ---
    vector() noexcept;
    vector(size_t n, const T& val);
    vector(size_t n);
    template <class InputIt, class = decltype(*std::declval<InputIt>())>
    vector(InputIt first, InputIt last);
    vector(const vector& other);
    vector(vector&& other) noexcept;
    ~vector();

    // --- Assignment ---
    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;
    bool operator==(const vector& other)const;
    bool operator!=(const vector& other)const;
    // --- Element access ---
    T& operator[](size_t i) noexcept;
    const T& operator[](size_t i) const noexcept;
    T& at(size_t i);
    const T& at(size_t i) const;
    T& front() noexcept;
    const T& front() const noexcept;
    T& back() noexcept;
    const T& back() const noexcept;

    // --- Iterator ---
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // --- Reverse Iterator ---
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // --- Capacity ---
    int size() const noexcept;
    int capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(int new_cap);
    void resize(int new_size);
    // --- Modifiers ---
    void push_back(T value);
	void pop_back();
	void insert(const_iterator pos, const T& value);
	void insert(const_iterator pos, size_t count, const T& value);
    void insert(const_iterator pos, const_iterator first, const_iterator last);
    void erase(const_iterator pos);
    void erase(const_iterator first, const_iterator last);
    void clear() noexcept;
    void swap(vector& other) noexcept;

    // --- Data ---
    T* data() noexcept;
    const T* data() const noexcept;

private:
    T* _ptr;
    int _size;
    int _cap;
};

template <class T>
void swap(vector<T>& a, vector<T>& b) noexcept;

} // namespace ccystd

#include "vector.impl.h"
