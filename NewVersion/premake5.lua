workspace "MarkdownParser"
    configurations { "Debug", "Release"}

    project "MarkdownParser"
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
        files { "MarkdownParser.hpp", "MarkdownParser.cpp" }
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        filter {}
        targetdir "bin/%{cfg.buildcfg}/"