#pragma once

#include <cstddef>
#include <type_traits>

namespace ccystd {

// --- reverse_iterator ---
template <class Iterator>
class reverse_iterator_t {
public:
    using value_type = typename std::remove_reference_t<decltype(*Iterator{})>;

    reverse_iterator_t() = default;
    explicit reverse_iterator_t(Iterator it);

    Iterator base() const;

    value_type& operator*() const;
    value_type* operator->() const;

    reverse_iterator_t& operator++();
    reverse_iterator_t& operator--();
    reverse_iterator_t operator++(int);
    reverse_iterator_t operator--(int);

    bool operator==(const reverse_iterator_t& other) const;
    bool operator!=(const reverse_iterator_t& other) const;

private:
    Iterator _current;
};

} // namespace ccystd

#include "iterator.impl.h"
