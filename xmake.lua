add_rules("mode.debug", "mode.release")
set_project("dig-logger")
set_version("2.0.0")
set_languages("c++20")

target("dig-logger")
    add_rules("utils.merge.archive")
    set_kind("static")
    add_deps("core", {public=true})
    add_deps("util-filter", {public=true})
    set_policy("build.merge_archive", true)

includes("core")
includes("util/filter")