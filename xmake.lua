add_rules("mode.debug", "mode.release")
set_project("dig-logger")
set_version("2.1.0")
set_languages("c++20")

target("dig-logger")
    set_kind("static")
    add_deps("core", {public=true})
    add_deps("util-filter", {public=true})
    add_deps("util-union", {public=true})
    add_deps("printer-stream", {public=true})
    add_deps("printer-stdout", {public=true})
    add_deps("printer-plain", {public=true})
    add_deps("printer-html", {public=true})
    add_files("core/src/dummy.cpp")
    set_policy("build.merge_archive", true)
    after_load(function (target)
        local includes = {}
        function cp_headerfiles(deps)
            for _, dep in pairs(deps) do
                local headers = dep:get("headerfiles")
                if type(headers) == "string" then
                    includes[headers] = true
                elseif type(headers) == "table" then
                    for _, header in pairs(headers) do
                        includes[header] = true
                    end
                end
                cp_headerfiles(dep:orderdeps())
            end
        end
        cp_headerfiles(target:orderdeps())
        for header, _ in pairs(includes) do
            target:add("headerfiles", header)
        end
    end)
target_end()

includes("core")
includes("util/filter")
includes("util/union")
includes("printer/formatter")
includes("printer/stream")
includes("printer/stdout")
includes("printer/plain")
includes("printer/html")

includes("test")

target("demo")
    set_default(false)
    set_kind("binary")
    add_deps("dig-logger")
    add_files("demo/demo.cpp")