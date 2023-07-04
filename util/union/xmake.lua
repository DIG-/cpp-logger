add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("util-union")
    set_default(false)
    set_kind("static")
    add_includedirs("include", {public=true})
    add_deps("core")