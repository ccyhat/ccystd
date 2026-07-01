# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ccystd")

# 头文件搜索路径
include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}")

# 可执行文件源文件
set(SOURCES
    "examples/main.cpp"
    "tests/VectorTest.cpp"
)

# 可执行文件
add_executable(ccystd ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ccystd PROPERTY CXX_STANDARD 20)
endif()
