workspace "Expression-Parser"
	configurations {"Debug", "Release"}
	language "C++"

project "parser"
	kind "ConsoleApp"
	targetdir "bin/%{cfg.buildcfg}"
	files {"./example/**.cpp", "./src/**.cpp"}
	includedirs{"./include"}
	-- links {"pthread", "boost_program_options"}
	buildoptions {"--std=c++17"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"