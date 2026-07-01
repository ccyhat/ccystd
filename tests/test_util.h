#pragma once

namespace ccystd {
namespace test {

// Compare two containers element by element
template <class Container1, class Container2>
bool container_equal(const Container1& lhs, const Container2& rhs) {
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();
    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (*it1 != *it2) return false;
    }
    return (it1 == lhs.end()) && (it2 == rhs.end());
}
} 
} // namespace ccystd
