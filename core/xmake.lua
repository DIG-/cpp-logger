add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("core")
    set_kind("static")
    add_includedirs("include", {public=true})
