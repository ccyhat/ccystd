#pragma once

#include "ccystd/vector.h"
#include <vector>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

namespace ccystd {
namespace VectorTest {

    template<class T>
    using stdVec = std::vector<T>;

    template<class T>
    using ccVec = ccystd::vector<T>;

    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();
    void testCase5();
    void testCase6();
    void testCase7();
    void testCase8();
    void testCase9();
    void testCase10();
    void testCase11();
    void testCase12();
    void testCase13();
    void testCase14();
    void testCase15();

    void testAllCases();

} // namespace VectorTest
} // namespace ccystd
