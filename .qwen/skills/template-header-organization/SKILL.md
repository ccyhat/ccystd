---
name: template-header-organization
description: C++ header-only template library file structure — .h declarations + .impl.h definitions + raw pointer iterator typedefs
source: auto-skill
extracted_at: '2026-06-08T05:30:40.412Z'
---

## Template Header Organization (.h + .impl.h)

For header-only C++ template libraries (like ccystd), separate declarations from definitions:

### File Structure

```
include/ccystd/
├── container.h          # Class declaration + method signatures only
├── container.impl.h     # All template method definitions
└── master_header.h      # #includes all modules in dependency order
```

### container.h (Declarations)

- Contains `#pragma once`, forward includes, namespace, class declaration
- Only method signatures — **no method bodies**
- Simple `using` aliases for iterators when they're just pointer typedefs:
  ```cpp
  using iterator       = T*;
  using const_iterator = const T*;
  ```
- **Last line** includes the implementation file:
  ```cpp
  #include "container.impl.h"
  ```

### container.impl.h (Definitions)

- `#pragma once` + necessary includes
- All template method definitions using `template <class T>` syntax:
  ```cpp
  template <class T>
  ReturnType container<T>::methodName(Params) { ... }
  ```
- Free functions:
  ```cpp
  template <class T>
  void swap(container<T>& a, container<T>& b) noexcept { ... }
  ```

### CMakeLists.txt

Add the `.impl.h` to `target_sources` so CMake tracks header changes:

```cmake
target_sources(lib_name INTERFACE
    "${CMAKE_SOURCE_DIR}/include/container.h"
    "${CMAKE_SOURCE_DIR}/include/container.impl.h"
)
```

### Why this pattern?

1. **Readability** — `.h` shows the full API surface at a glance
2. **Stdlib pattern** — follows how `<vector>` internally uses `__vector.tcc`
3. **Template requirement** — both must be headers (templates can't go in `.cpp`)
4. **Iterator typedefs** — when iterators are just `T*` wrappers, use `using` aliases instead of nested classes. No need for operator overloads since `T*` already supports `*`, `++`, `--`, `==`, `!=`, `[]`, `+`, `-` natively.
