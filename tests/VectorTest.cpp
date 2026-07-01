// VectorTest.cpp - Ported from TinySTL VectorTest
// Tests for ccystd::vector
// Tests for missing features are commented out with // TODO markers.

#include "tests/vector_test.h"
#include "tests/test_util.h"

namespace ccystd {
namespace VectorTest {

// testCase1: fill constructor, range constructor
 void testCase1()
 {
     std::vector<std::string> v1(10, "zxh");
     ccystd::vector<std::string> v2(10, "zxh");
     assert(test::container_equal(v1, v2));

     std::vector<std::string> v3(10);
     ccystd::vector<std::string> v4(10);
     assert(test::container_equal(v3, v4));

     std::array<std::string, 3> arr = { "abc", "def", "ghi" };
     std::vector<std::string> v5(std::begin(arr), std::end(arr));
     ccystd::vector<std::string> v6(std::begin(arr), std::end(arr));
     assert(test::container_equal(v5, v6));
 }

// testCase2: copy/move constructor and assignment
// TODO: enable after implementing vector(n, value)
 void testCase2()
 {
     std::vector<int> temp1(10, 0);
     ccystd::vector<int> temp2(10, 0);

     auto v1(temp1);
     auto v2(temp2);
     assert(test::container_equal(v1, v2));

     auto v3(std::move(temp1));
     auto v4(std::move(temp2));
     assert(test::container_equal(v3, v4));

     auto v5 = v1;
     auto v6 = v2;
     assert(test::container_equal(v5, v6));

     auto v7 = std::move(v3);
     auto v8 = std::move(v4);
     assert(test::container_equal(v7, v8));
 }

// testCase3: operator== and operator!=
// TODO: enable after implementing operator== and operator!=
 void testCase3()
 {
     ccystd::vector<int> v1, v2;
     for (int i = 0; i != 100; ++i) {
         v1.push_back(i);
         v2.push_back(i);
     }
     assert(v1 == v2);
     assert(!(v1 != v2));
 }

// testCase4: iterator traversal - PASS
void testCase4()
{
    ccystd::vector<int> myvector;
    for (int i = 1; i <= 5; i++) myvector.push_back(i);

    auto i = 1;
    for (ccystd::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, ++i) {
        assert(*it == i);
    }

    i = 1;
    for (ccystd::vector<int>::const_iterator it = myvector.cbegin(); it != myvector.cend(); ++it, ++i) {
        assert(*it == i);
    }
}

// testCase5: reverse_iterator
// TODO: enable after implementing reverse_iterator
 void testCase5()
 {
     ccystd::vector<int> myvector(5);
     int i = 0;
     ccystd::vector<int>::reverse_iterator rit = myvector.rbegin();
     for (; rit != myvector.rend(); ++rit)
         *rit = ++i;

     i = 5;
     for (ccystd::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, --i) {
         assert(*it == i);
     }

     i = 1;
     for (ccystd::vector<int>::reverse_iterator it = myvector.rbegin(); it != myvector.rend(); ++it, ++i) {
         assert(*it == i);
     }
 }

// testCase6: resize
// TODO: enable after implementing resize
 void testCase6()
 {
     ccystd::vector<int> v(11, 0);
     assert(v.size() == 11);
     v.resize(5);
     assert(v.size() == 5);
     v.resize(20);
     assert(v.size() == 20);
 }

// testCase7: reserve / capacity - PASS
void testCase7()
{
    ccystd::vector<int> v;
    v.reserve(20);
    assert(v.capacity() == 20);
}

// testCase8: operator[], front, back
// TODO: enable after implementing vector(n)
 void testCase8()
 {
     std::vector<int> v1(10);
     ccystd::vector<int> v2(10);
     for (unsigned i = 0; i < 10; i++) {
         v1[i] = i;
         v2[i] = i;
     }
     assert(test::container_equal(v1, v2));

     v1.front() = 99;
     v2.front() = 99;
     v1.back() = 100;
     v2.back() = 100;

     assert(test::container_equal(v1, v2));
 }

// testCase9: data()
// TODO: enable after implementing vector(n)
 void testCase9()
 {
     std::vector<int> v1(5);
     ccystd::vector<int> v2(5);

     auto p1 = v1.data();
     auto p2 = v2.data();
     *p1 = 10; ++p1; *p1 = 20; p1[2] = 100;
     *p2 = 10; ++p2; *p2 = 20; p2[2] = 100;

     assert(test::container_equal(v1, v2));
 }

// testCase10: swap
// TODO: enable after implementing vector(n, value)
 void testCase10()
 {
     ccystd::vector<int> foo(3, 100);
     ccystd::vector<int> bar(2, 200);
     foo.swap(bar);
 }

// testCase11: push_back + pop_back
// TODO: enable after implementing pop_back
 void testCase11()
 {
     std::vector<std::string> v1;
     ccystd::vector<std::string> v2;
     v1.push_back("hello "); v1.push_back("world");
     v2.push_back("hello "); v2.push_back("world");
     assert(test::container_equal(v1, v2));
     v1.pop_back();
     v2.pop_back();
     assert(test::container_equal(v1, v2));
 }

// testCase12: insert (multiple overloads)
// TODO: enable after implementing insert
 void testCase12()
 {
     std::vector<int> v1;
     ccystd::vector<int> v2;
     v1.insert(v1.begin(), 0);
     v2.insert(v2.begin(), 0);
     assert(test::container_equal(v1, v2));

     v1.insert(v1.end(), 1);
     v2.insert(v2.end(), 1);
     assert(test::container_equal(v1, v2));

     v1.insert(v1.begin() + v1.size() / 2, 10, 0);
     v2.insert(v2.begin() + v2.size() / 2, 10, 0);
     assert(test::container_equal(v1, v2));

     int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
     v1.insert(v1.end(), std::begin(arr), std::end(arr));
     v2.insert(v2.end(), std::begin(arr), std::end(arr));
     assert(test::container_equal(v1, v2));
 }

// testCase13: erase (single element and range)
void testCase13()
{
    std::vector<int> v1;
    ccystd::vector<int> v2;
    for (int i = 1; i <= 10; i++) {
        v1.push_back(i);
        v2.push_back(i);
    }
    v1.erase(v1.begin() + 5);
    v2.erase(v2.begin() + 5);
    assert(test::container_equal(v1, v2));

    v1.erase(v1.begin(), v1.begin() + 3);
    v2.erase(v2.begin(), v2.begin() + 3);
    assert(test::container_equal(v1, v2));
}

// testCase14: operator== and operator!= comparison
// TODO: enable after implementing operator== and operator!=
 void testCase14()
 {
     ccystd::vector<int> foo(3, 100);
     ccystd::vector<int> bar(2, 200);
     assert(!(foo == bar));
     assert(foo != bar);
 }

class TestItem {
public:
    TestItem() { ++count; }
    TestItem(const TestItem&) { ++count; }
    virtual ~TestItem() { --count; }
    static int getCount() { return count; }
    static int count;
};
int TestItem::count = 0;

// testCase15: memory leak detection (construct/destruct count)
void testCase15()
{
    TestItem::count = 0;
    assert(TestItem::getCount() == 0);
    {
        ccystd::vector<TestItem> t(10);
        t.push_back(TestItem());
        t.push_back(TestItem());
        t.push_back(TestItem());
        t.insert(t.begin(), t.begin(), t.begin() + 1);
    }
    assert(TestItem::getCount() == 0);
}

void testAllCases()
{
    testCase1();   // TODO: fill ctor, range ctor
    testCase2();   // TODO: fill ctor
    testCase3();   // TODO: operator==
    testCase4();
    testCase5();   // TODO: reverse_iterator
    testCase6();   // TODO: resize
    testCase7();
    testCase8();   // TODO: vector(n)
    testCase9();   // TODO: vector(n)
    testCase10();  // TODO: vector(n, value)
    testCase11();  // TODO: pop_back
    testCase12();  // TODO: insert
    testCase13();
    testCase14();  // TODO: operator==
    testCase15();
}
} // namespace VectorTest
} // namespace ccystd
