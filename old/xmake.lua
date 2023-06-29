add_rules("mode.debug", "mode.release")

target("DIG-Logger")
    set_kind("static")
    set_version("1.1.1")
    add_defines("DIG_LOGGER_STATIC")
    add_includedirs("include", {public = true})
    add_files("src/*.cpp")