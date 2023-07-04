add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("printer-html")
    set_default(false)
    set_kind("static")
    add_deps("core")
    add_deps("printer-stream")
    add_deps("printer-formatter")
    add_includedirs("include", {public=true})
    add_files("src/html.cpp")