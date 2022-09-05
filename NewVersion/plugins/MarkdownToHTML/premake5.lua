workspace "Plugin__Markdown_to_HTML"
    configurations { "Debug", "Release"}

    project "Plugin__Markdown_to_HTML"
        kind "ConsoleApp"
        --[[
            Dev version
            files { "**.hpp", "**.cpp" }
            includedirs { "include" }
        ]]
        --[[
            Release version
            files { "**.hpp", "**.cpp" }
        ]]
        files { "**.hpp", "**.cpp" }
        includedirs { "include" }
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        filter {}
        targetdir "bin/%{cfg.buildcfg}/"