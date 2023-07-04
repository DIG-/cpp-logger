add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("printer-stream")
    set_default(false)
    set_kind("headeronly")
    set_group("print")
    add_includedirs("include", {public=true})
    add_deps("core")