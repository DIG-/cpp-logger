add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("core")
    set_default(false)
    set_kind("static")
    set_filename("core")
    add_includedirs("include", {public=true})
