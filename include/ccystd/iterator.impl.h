#pragma once

namespace ccystd {

template <class Iterator>
reverse_iterator_t<Iterator>::reverse_iterator_t(Iterator it) : _current(it) {}

template <class Iterator>
Iterator reverse_iterator_t<Iterator>::base() const { return _current; }

template <class Iterator>
typename reverse_iterator_t<Iterator>::value_type& reverse_iterator_t<Iterator>::operator*() const {
    auto tmp = _current;
    return *(--tmp);  // dereference the previous element
}

template <class Iterator>
typename reverse_iterator_t<Iterator>::value_type* reverse_iterator_t<Iterator>::operator->() const {
    auto tmp = _current;
    return --tmp;
}

template <class Iterator>
reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator++() {
    --_current;  // reverse ++ = forward --
    return *this;
}

template <class Iterator>
reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator--() {
    ++_current;  // reverse -- = forward ++
    return *this;
}

template <class Iterator>
reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator++(int) {
    reverse_iterator_t tmp = *this;
    --_current;
    return tmp;
}

template <class Iterator>
reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator--(int) {
    reverse_iterator_t tmp = *this;
    ++_current;
    return tmp;
}

template <class Iterator>
bool reverse_iterator_t<Iterator>::operator==(const reverse_iterator_t& other) const {
    return _current == other._current;
}

template <class Iterator>
bool reverse_iterator_t<Iterator>::operator!=(const reverse_iterator_t& other) const {
    return _current != other._current;
}

} // namespace ccystd
