package("dig-logger")
    set_homepage("https://github.com/DIG-/cpp-logger")
    set_description("A C++ logger api with support to extensions.")
    set_license("CC BY-ND 4.0")

    add_urls("https://github.com/DIG-/cpp-logger/archive/refs/tags/$(version).zip", {alias="zip"})
    add_urls("https://github.com/DIG-/cpp-logger.git", {alias="git"})

    add_versions("zip:2.0.1", "6a0034f410b969b6d88ef260727d52ef70a4b4b46003179d74ad96339a1568ed")
    add_versions("git:2.0.1", "123ad0f4a90c1ca64f0fc170cb9bc3e6a06718d6")
    add_versions("zip:2.0.0", "4535ef2b07554631903604ca20153af81cb7175e7faa169082fd17e405ad51f2")
    add_versions("git:2.0.0", "8dd72936ed3c9012abe80961fb6abb08c26b9e3c")

    on_install(function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:has_cxxincludes("source_location"))
    end)
