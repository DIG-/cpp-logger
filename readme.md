DIG Logger
=================
[![Build Status](https://img.shields.io/appveyor/build/DIG-/cpp-logger/master?logo=appveyor&logoColor=dddddd)](https://ci.appveyor.com/project/DIG-/cpp-logger/branch/master)
[![Test Status](https://img.shields.io/appveyor/tests/DIG-/cpp-logger/master?logo=appveyor&logoColor=dddddd)](https://ci.appveyor.com/project/DIG-/cpp-logger/branch/master)
[![Version](https://img.shields.io/badge/version-2.0.0-brightgreen
)](https://github.com/DIG-/cpp-logger)
[![License](https://img.shields.io/badge/license-CC%20BY--ND%204.0-blue)](https://creativecommons.org/licenses/by-nd/4.0/)

[![Windows - Supported](https://img.shields.io/badge/windows-supported-success?logo=windows&logoColor=dddddd)](#)
[![Linux - Supported](https://img.shields.io/badge/linux-supported-success?logo=linux&logoColor=dddddd)](#)
[![MacOS - Not-Tested](https://img.shields.io/badge/macos-not--tested-orange?logo=apple&logoColor=dddddd)](#)

A C++ logger api with support to extensions.

Requires C++20.
| Compiler |  gcc  |  clang  |       msvc       |
|----------|-------|---------|------------------|
| Required | 11.1+ | 12.0.1+ | 19.29+ (VS16.10) |

Usage
=====
```cpp
#include <dig-logger/logger.hpp>
#include <dig-logger/printer/stdout.hpp>
⋮
DIG::Logger::Logger log(std::make_shared<DIG::Logger::Printer::StdOut>());
⋮
// Long names
log1.assert("Assert");
log.error("Error");
log.warning("Warning");
log.information("Information");
log.debug("Debug");
log.verbose("Verbose");

// Short names
log.e("Error");
log.w("Warning");
log.i("Information");
log.d("Debug");
log.v("Verbose");
```

Instalation
===========
Under construction

License
=======
[CC BY-ND 4.0](https://creativecommons.org/licenses/by-nd/4.0/)

- You can use and re-dist freely.
- You can also modify, but only for yourself.
- You can use it as a part of your project, but without modifications in this project.