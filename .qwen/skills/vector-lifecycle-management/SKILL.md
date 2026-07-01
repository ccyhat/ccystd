---
name: vector-lifecycle-management
description: Correct memory lifecycle patterns for custom vector implementation — placement new, explicit destruct, iterator invalidation, self-insertion
source: auto-skill
extracted_at: '2026-06-17T08:23:18.855Z'
---

# Custom Vector Memory Lifecycle

When implementing a `vector` with raw memory allocation (`::operator new` + `::operator delete`), these patterns are mandatory for correctness with non-trivial types (e.g., `std::string`):

## Construct in raw memory — placement new, NOT assignment

```cpp
// WRONG: operator= on an unconstructed object → UB
_ptr[_size++] = value;

// CORRECT: placement new constructs the object in place
new (_ptr + _size) T(std::move(value));
_size++;
```

This applies to `push_back`, `insert`, `resize`, and any constructor that fills raw memory. The pattern matches what `reserve` already does during relocation:

```cpp
// D:\cplusplus\ccystd\include\ccystd\vector.impl.h — reserve()
new (new_mem + i) T(std::move(_ptr[i]));  // construct in new memory
_ptr[i].~T();                              // destruct in old memory
```

## Destruct before shrinking or deallocating

```cpp
// pop_back: destruct last element before reducing size
void pop_back() {
    _ptr[--_size].~T();
}

// clear: destruct ALL elements before zeroing size
void clear() noexcept {
    for (int i = 0; i < _size; ++i) {
        _ptr[i].~T();
    }
    _size = 0;
}

// destructor: destruct all elements before freeing memory
~vector() {
    if (_ptr) {
        for (int i = 0; i < _size; ++i) {
            _ptr[i].~T();
        }
        ::operator delete(_ptr);
    }
}
```

For trivial types (`int`, `double`) the destructor is a no-op, so this is always safe.

## Iterator invalidation: calculate offsets BEFORE reserve

`reserve()` may reallocate memory, invalidating all existing iterators/pointers. Always compute indices first:

```cpp
void insert(const_iterator pos, const T& value) {
    size_t index = pos - begin();    // ← calculate BEFORE reserve
    if (_size == _cap) reserve(...); // reserve may invalidate pos
    // ... use index, not pos
}
```

## Self-insertion: detect and handle overlapping source/dest

When `insert(pos, first, last)` is called with `first`/`last` pointing to the same vector (e.g., `v.insert(pos, v.begin(), v.end())`), `reserve` invalidates those pointers. Detect this case and use offsets:

```cpp
void insert(const_iterator pos, const_iterator first, const_iterator last) {
    size_t count = last - first;
    if (count == 0) return;

    size_t index = pos - begin();

    // Detect: does first point into our own memory?
    bool is_self = (first >= begin() && first < end());
    size_t first_offset = is_self ? (first - begin()) : 0;

    if (_size + count > _cap) reserve(_size + count);

    // ... move elements, then:

    if (is_self) {
        // Re-locate after potential reallocation
        const_iterator real_first = begin() + first_offset;
        for (size_t i = 0; i < count; ++i) {
            new (_ptr + index + i) T(*(real_first + i));
        }
    } else {
        // External range: safe to use directly
        for (size_t i = 0; i < count; ++i) {
            new (_ptr + index + i) T(*(first + i));
        }
    }
}
```
