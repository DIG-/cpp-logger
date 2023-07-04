add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("printer-formatter")
    set_default(false)
    set_kind("static")
    add_deps("core")
    add_includedirs("include", {public=true})
    add_files("src/formatter.cpp")