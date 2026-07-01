#pragma once

#include <utility>

namespace ccystd {

template <class T>
vector<T>::vector() noexcept : _ptr(nullptr), _size(0), _cap(0) {}

template <class T>
vector<T>::vector(size_t n, const T& val) {
    if (n == 0) return;
    // allocate memory
    _ptr = static_cast<T*>(::operator new(n * sizeof(T)));
    // construct objects on the allocated memory
    for (size_t i = 0; i < n; ++i) {
        new (_ptr + i) T(val);
    }
    _size = n;
    _cap = n;
}

template <class T>
vector<T>::vector(size_t n) {
    _ptr = static_cast<T*>(::operator new(n * sizeof(T)));
    for (size_t i = 0; i < n; ++i) {
        new (_ptr + i) T();
    }
    _size = n;
    _cap = n;
}

template <class T>
vector<T>::vector(const vector& other) : vector() {
    reserve(other._size);
    for (int i = 0; i < other._size; ++i) _ptr[_size++] = other._ptr[i];
}

template <class T>
vector<T>::vector(vector&& other) noexcept
    : _ptr(other._ptr), _size(other._size), _cap(other._cap) {
    other._ptr = nullptr;
    other._size = 0;
    other._cap = 0;
}

template <class T>
vector<T>::~vector() {
    if (_ptr) {
        for (int i = 0; i < _size; ++i) {
            _ptr[i].~T();
        }
        ::operator delete(_ptr);
    }
}

template <class T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        clear();
        reserve(other._size);
        for (int i = 0; i < other._size; ++i) _ptr[_size++] = other._ptr[i];
    }
    return *this;
}

template <class T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this != &other) {
        clear();
        if (_ptr) ::operator delete(_ptr);
        _ptr = other._ptr;
        _size = other._size;
        _cap = other._cap;
        other._ptr = nullptr;
        other._size = 0;
        other._cap = 0;
    }
    return *this;
}
template <class T>
bool vector<T>:: operator==(const vector& other)const {
    if (this->_size != other._size)
        return false;
    for (size_t i = 0; i < this->_size; i++)
    {
        if (this->_ptr[i] != other._ptr[i])
            return false;
    }
    return true;
}
template <class T>
bool vector<T>:: operator!=(const vector& other)const {   
    return !(*this == other);
}

template <class T>
void vector<T>::push_back(T value) {
    if (_size == _cap) reserve(_cap == 0 ? 4 : _cap * 2);
	new (_ptr + _size) T(std::move(value));
	_size++;
}
template <class T>
void vector<T>::pop_back() {
	_ptr[--_size].~T();
}
template <class T>
void vector<T>::insert(const_iterator pos, const T& value) {
    size_t index = pos - begin();
    if (_size == _cap) {
        reserve(_cap == 0 ? 4 : _cap * 2);
    }

    // shift elements right, make room for new element
    for (size_t i = _size; i > index; --i) {
        new (_ptr + i) T(std::move(_ptr[i - 1]));
        _ptr[i - 1].~T();
	}
    new (_ptr + index) T(value);  
    _size++;
}
template<class T>
void vector<T>::insert(const_iterator pos, size_t count, const T& value) {
    size_t index = pos - begin();
    if (_size + count > _cap) {
        reserve(_size + count);
    }
    // shift elements right, make room for new elements
    for (size_t i = _size + count - 1; i >= index + count; --i) {
        new (_ptr + i) T(std::move(_ptr[i - count]));
        _ptr[i - count].~T();
    }
    for (size_t i = 0; i < count; ++i) {
        new (_ptr + index + i) T(value);
    }
    _size += count;
}
template<class T>
void vector<T>::insert(const_iterator pos, const_iterator first, const_iterator last) {
    size_t count = last - first;
    if (count == 0) return;

    size_t index = pos - begin();

    // handle self-insertion: check if first is within current vector range
    bool is_self = (first >= begin() && first < end());
    size_t first_offset = is_self ? (first - begin()) : 0;

    if (_size + count > _cap) {
        reserve(_size + count);
    }

    // shift existing elements
    for (size_t i = _size + count - 1; i >= index + count; --i) {
        new (_ptr + i) T(std::move(_ptr[i - count]));
        _ptr[i - count].~T();
    }

    // copy elements
    if (is_self) {
        // self-insertion: reserve invalidates pointers, recalculate offset to reposition
        const_iterator real_first = begin() + first_offset;
        for (size_t i = 0; i < count; ++i) {
            new (_ptr + index + i) T(*(real_first + i));
        }
    } else {
        // external range: directly use first/last
        for (size_t i = 0; i < count; ++i) {
            new (_ptr + index + i) T(*(first + i));
        }
    }

    _size += count;
}
template <class T>
void vector<T>::erase(const_iterator pos) {
    size_t index = pos - begin();
    for (size_t i = index; i + 1 < static_cast<size_t>(_size); ++i) {
        new (_ptr + i) T(std::move(_ptr[i + 1]));
        _ptr[i + 1].~T();
    }
    _ptr[_size - 1].~T();
    _size--;
}
template <class T>
void vector<T>::erase(const_iterator first, const_iterator last) {
    size_t index = first - begin();
    size_t count = last - first;
    if (count == 0) return;
    for (size_t i = index; i + count < static_cast<size_t>(_size); ++i) {
        new (_ptr + i) T(std::move(_ptr[i + count]));
        _ptr[i + count].~T();
    }
    for (size_t i = _size - count; i < static_cast<size_t>(_size); ++i) {
        _ptr[i].~T();
    }
    _size -= count;
}
template <class T>
T* vector<T>::data() noexcept { return _ptr; }

template <class T>
const T* vector<T>::data() const noexcept { return _ptr; }

template <class T>
int vector<T>::size() const noexcept { return _size; }

template <class T>
int vector<T>::capacity() const noexcept { return _cap; }

template <class T>
bool vector<T>::empty() const noexcept { return _size == 0; }

template <class T>
void vector<T>::clear() noexcept {
    for (int i = 0; i < _size; ++i) {
        _ptr[i].~T();
    }
    _size = 0;
}

template <class T>
void vector<T>::swap(vector& other) noexcept {
    std::swap(_ptr, other._ptr);
    std::swap(_size, other._size);
    std::swap(_cap, other._cap);
}
template <class T>
void vector<T>::resize(int new_size) {
    if (new_size < _size) {
        _size = new_size;
    } else if (new_size > _size) {
        reserve(new_size);
        for (int i = _size; i < new_size; ++i) {
            new (_ptr + i) T();
        }
        _size = new_size;
    }
}
template <class T>
T& vector<T>::operator[](size_t i) noexcept { return _ptr[i]; }

template <class T>
const T& vector<T>::operator[](size_t i) const noexcept { return _ptr[i]; }

template <class T>
T& vector<T>::at(size_t i) {
    if (i >= static_cast<size_t>(_size)) throw "vector::at: index out of range";
    return _ptr[i];
}

template <class T>
const T& vector<T>::at(size_t i) const {
    if (i >= static_cast<size_t>(_size)) throw "vector::at: index out of range";
    return _ptr[i];
}

template <class T>
T& vector<T>::front() noexcept { return _ptr[0]; }

template <class T>
const T& vector<T>::front() const noexcept { return _ptr[0]; }

template <class T>
T& vector<T>::back() noexcept { return _ptr[_size - 1]; }

template <class T>
const T& vector<T>::back() const noexcept { return _ptr[_size - 1]; }

template <class T>
typename vector<T>::iterator vector<T>::begin() noexcept { return _ptr; }

template <class T>
typename vector<T>::iterator vector<T>::end() noexcept { return _ptr + _size; }

template <class T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept { return _ptr; }

template <class T>
typename vector<T>::const_iterator vector<T>::end() const noexcept { return _ptr + _size; }

template <class T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept { return _ptr; }

template <class T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept { return _ptr + _size; }

template <class T>
void vector<T>::reserve(int new_cap) {
    if (new_cap <= _cap) return;
    T* new_mem = static_cast<T*>(::operator new(new_cap * sizeof(T)));
    for (int i = 0; i < _size; ++i) {
        new (new_mem + i) T(std::move(_ptr[i]));
        _ptr[i].~T();
    }
    if (_ptr) ::operator delete(_ptr);
    _ptr = new_mem;
    _cap = new_cap;
}

template <class T>
void swap(vector<T>& a, vector<T>& b) noexcept { a.swap(b); }

template <class T>
typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
    return reverse_iterator(end());
}

template <class T>
typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
    return reverse_iterator(begin());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
    return const_reverse_iterator(cend());
}

template <class T>
typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
    return const_reverse_iterator(cbegin());
}

} // namespace ccystd
