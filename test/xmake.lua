add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("test-core-logger")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/core/logger.cpp")

target("test-core-null-safety")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/core/null-safety.cpp")

target("test-filter-forwarding")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/filter/forwarding.cpp")

target("test-filter-minimum")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/filter/minimum.cpp")

target("test-filter-maximum")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/filter/maximum.cpp")

target("test-filter-null-safety")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/filter/null-safety.cpp")

target("test-union-forwarding")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/union/forwarding.cpp")

target("test-union-null-safety")
    set_default(false)
    set_kind("binary")
    set_group("test")
    set_optimize("none")
    add_deps("dig-logger")
    add_files("src/union/null-safety.cpp")