# AGENTS.md

## Build & Run

```powershell
# Configure (from Developer PowerShell / VS Native Tools command prompt)
cmake --preset x64-debug

# Build
cmake --build --preset x64-debug

# Run (tests execute inside the single executable)
.\out\build\x64-debug\ccystd.exe
```

There is no separate test runner. All tests run via `examples/main.cpp` → `testAllCases()`.

## Architecture

- **Header-only** template library reimplementing C++ STL containers.
- `include/ccystd/` — library headers. Each component has a `.h` (declarations) and `.impl.h` (definitions, included at the bottom of `.h`).
- `tests/` — assert-based tests (no framework). `VectorTest.cpp` contains test cases; `vector_test.h` declares them; `test_util.h` provides `container_equal`.
- `examples/main.cpp` — sole entry point; calls `testAllCases()`.
- All code lives in `namespace ccystd`.

## Key Conventions

- C++20, MSVC (`cl.exe`), Ninja generator, Windows-only presets.
- Tests compare `ccystd::vector` against `std::vector` element-by-element using `test::container_equal`.
- Test cases marked `// TODO: enable after implementing ...` are disabled because the feature is not yet implemented. When adding a feature, uncomment the corresponding test case and remove its TODO.
- Memory uses `::operator new` + placement new / explicit destructor calls — not `malloc`/`free`.
- Comments are in Chinese.

## Adding a New Container

1. Create `include/ccystd/<name>.h` + `<name>.impl.h` following the `vector` pattern.
2. Add `#include "ccystd/<name>.h"` to `include/ccystd/ccystd.h`.
3. Add test file `tests/<Name>Test.cpp` + `tests/<name>_test.h`, mirroring the vector test structure.
4. Add both new `.cpp` files to the `SOURCES` list in `CMakeLists.txt`.
5. Wire the test into `examples/main.cpp`.
