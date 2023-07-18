add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("core")
    set_default(false)
    set_kind("static")
    add_includedirs("include", {public=true})
    add_headerfiles("include/(**)")
    add_files("src/logger.cpp")
    on_config(function(target)
        if not target:has_cxxincludes("source_location") then 
            raise("Require compiler with support to std::source_location")
        end
    end)
