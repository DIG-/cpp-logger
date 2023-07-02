add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("dig-logger")
    add_deps("core", {public=true})
    add_deps("util-filter", {public=true})
    set_kind("static")

includes("core")
includes("util/filter")