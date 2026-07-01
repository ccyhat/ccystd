---
name: project-structure
description: ccystd project folder layout — include/ for library headers, examples/ for demos, tests/ for test code
source: auto-skill
extracted_at: '2026-06-10T03:12:09.748Z'
---

## ccystd Project Folder Structure

```
ccystd/                          # Project root
├── CMakeLists.txt               # Top-level: project(), include_directories(), add_executable()
├── CMakePresets.json
├── include/
│   └── ccystd/
│       ├── ccystd.h             # Master header — includes all modules
│       ├── vector.h
│       ├── vector.impl.h
│       └── ...                  # Future containers
├── examples/
│   └── main.cpp                 # Demo / entry point
└── tests/
    ├── VectorTest.cpp
    ├── test_util.h
    └── vector_test.h
```

### Rules

1. **`include/ccystd/`** — only library headers (declarations + impl files). Nothing else.
2. **`examples/`** — demo source code that uses the library. Entry point lives here.
3. **`tests/`** — test source and headers. Not mixed into `include/`.
4. **Never nest a `ccystd/` subdirectory** under the project root — it confuses the library name with the demo directory.
5. **`ccystd.h`** (master header) lives inside `include/ccystd/`, not alongside demo code.

### CMakeLists.txt (top-level)

No `add_subdirectory` needed. Keep it flat:

```cmake
include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}")

set(SOURCES
    "examples/main.cpp"
    "tests/VectorTest.cpp"
)

add_executable(ccystd ${SOURCES})
```
