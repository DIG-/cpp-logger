add_rules("mode.debug", "mode.release")
set_project("dig-logger")
set_version("2.0.0")
set_languages("c++20")

target("dig-logger")
    set_kind("static")
    add_deps("core", {public=true})
    add_deps("util-filter", {public=true})
    add_files("core/src/dummy.cpp")
    set_policy("build.merge_archive", true)

includes("core")
includes("util/filter")

target("demo")
    set_default(false)
    set_kind("binary")
    add_deps("dig-logger")
    add_files("demo/demo.cpp")