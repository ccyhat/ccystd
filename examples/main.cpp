// main.cpp: 演示 ccystd::vector 的使用 + 运行测试

#include "ccystd/ccystd.h"
#include "tests/vector_test.h"
#include <iostream>

int main()
{
    std::cout << "Running ccystd::vector tests..." << std::endl;
    ccystd::VectorTest::testAllCases();
    std::cout << "All enabled tests passed!" << std::endl;
    return 0;
}
