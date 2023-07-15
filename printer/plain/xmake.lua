add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("printer-plain")
    set_default(false)
    set_kind("static")
    set_group("print")
    add_deps("core")
    add_deps("printer-stream")
    add_deps("printer-formatter")
    add_includedirs("include", {public=true})
    add_headerfiles("include/(**)")
    add_files("src/plain.cpp")