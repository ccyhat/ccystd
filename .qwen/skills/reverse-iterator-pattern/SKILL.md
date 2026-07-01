---
name: reverse-iterator-pattern
description: reverse_iterator for header-only template containers — must be a wrapper class, never a raw pointer typedef
source: auto-skill
extracted_at: '2026-06-10T07:54:58.809Z'
---

## reverse_iterator Implementation Pattern

### Key Rule: Cannot Be a Raw Pointer Typedef

Forward iterators can be simple `using iterator = T*;` because `ptr++` naturally moves forward. But **reverse_iterator must be a wrapper class** — you cannot change a raw pointer's built-in `++` operator.

```cpp
// Forward iterator: raw pointer works fine
using iterator = T*;          // ptr++ moves forward ✓

// Reverse iterator: MUST be a wrapper class
using reverse_iterator = T*;  // ptr++ still moves forward ✗ WRONG
```

### Implementation Structure

Define `reverse_iterator_t<Iterator>` **outside** the container class, then typedef inside:

```cpp
// In container.h — BEFORE the container class
template <class Iterator>
class reverse_iterator_t {
    Iterator current_;  // underlying forward iterator

public:
    explicit reverse_iterator_t(Iterator it);
    Iterator base() const;

    value_type& operator*() const;   // dereferences PREVIOUS element
    value_type* operator->() const;

    reverse_iterator_t& operator++();  // reverse ++ = forward --
    reverse_iterator_t& operator--();  // reverse -- = forward ++
    // ... post-increment, comparison operators
};

// Inside container class
using reverse_iterator       = reverse_iterator_t<T*>;
using const_reverse_iterator = reverse_iterator_t<const T*>;
```

### Critical Design: operator* Returns Previous Element

The reverse iterator wraps a forward iterator, but **`rbegin().base() == end()`**. So `*rbegin()` must return `*(base - 1)`:

```cpp
// rbegin() = reverse_iterator(end())
// *rbegin() = last element, not past-the-end!

value_type& operator*() const {
    auto tmp = current_;
    return *(--tmp);  // go back one, then dereference
}
```

### Mapping Between Forward and Reverse

| Reverse iterator | Wraps (base()) | Dereferences |
|---|---|---|
| `rbegin()` | `end()` | last element |
| `rend()` | `begin()` | one before first (undefined, like `end()`) |

### Vector Methods

```cpp
reverse_iterator rbegin() noexcept       { return reverse_iterator(end()); }
reverse_iterator rend() noexcept         { return reverse_iterator(begin()); }
const_reverse_iterator rbegin() const    { return const_reverse_iterator(end()); }
const_reverse_iterator rend() const      { return const_reverse_iterator(begin()); }
const_reverse_iterator crbegin() const   { return const_reverse_iterator(cend()); }
const_reverse_iterator crend() const     { return const_reverse_iterator(cbegin()); }
```

### C++20 Note

If you define `operator==`, C++20 auto-derives `operator!=` — no need to write it. But for reverse_iterator, still define both explicitly for clarity.

### File Encoding Warning

MSVC (cl.exe) has issues with non-ASCII comments in header files if not saved as UTF-8 with BOM. **Use English comments in `.impl.h` files** to avoid `C3878` / `C2760` syntax errors caused by garbled Chinese characters.
