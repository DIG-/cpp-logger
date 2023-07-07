add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("test-filter-minimum")
    set_default(false)
    set_kind("binary")
    set_group("test")
    add_deps("dig-logger")
    add_files("src/filter/minimum.cpp")