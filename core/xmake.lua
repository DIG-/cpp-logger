add_rules("mode.debug", "mode.release")
set_languages("c++20")

target("core")
    set_default(false)
    set_kind("headeronly")
    add_includedirs("include", {public=true})
    on_config(function(target)
        if not target:has_cxxincludes("source_location") then 
            raise("Require compiler with support to std::source_location")
        end
    end)
