add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("printer-stdout")
    set_default(false)
    set_kind("static")
    set_group("print")
    set_filename("print-stdout")
    add_deps("core")
    add_deps("printer-stream")
    add_deps("printer-formatter")
    add_includedirs("include", {public=true})
    add_files("src/stdout.cpp")
    if is_plat("windows", "mingw") then
        add_files("src/color/windows.cpp")
    else
        add_files("src/color/linux.cpp")
    end