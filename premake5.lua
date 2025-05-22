workspace "suiCune"
startproject "suiCune"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    buildlog  ("bin-obj/" .. outputdir .. "%{prj.name}.log")

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	warnings "extra"

	syslibdirs {
        ".\\deps\\SDL2\\lib\\x86\\",
        ".\\deps\\physfs\\lib\\x86\\",
		".\\lib\\libmobile\\"
	}

	includedirs {
		".\\src\\",
        ".\\deps\\SDL2\\include\\",
        ".\\deps\\physfs\\include\\"
	}

	platforms {
		"x86",
		"x86_64",
	}

	configurations {
		"Release",
		"Debug",
	}

	filter "Release"
		defines "NDEBUG"
		optimize "On"
		runtime "Release"
		symbols "Off"

	filter "Debug"
		defines "DEBUG"
		optimize "Debug"
		runtime "Debug"
		symbols "On"

	filter "platforms:x86"
		architecture "x86"

	filter "platforms:x86_64"
		architecture "x86_64"

	project "libmobile"
		targetname "libmobile"
		language "c"
		kind "StaticLib"

		files {
			".\\lib\\libmobile\\**.c",
			".\\lib\\libmobile\\**.h",
		}
	
	project "maps"
		targetname "maps"
		language "c"
		kind "StaticLib"

		files {
			".\\maps\\**.c",
			".\\maps\\**.h",
		}

	project "suiCune"
		targetname "suiCune"
		targetdir (".")
		language "c"
		kind "windowedapp"
		warnings "off"

		links {
            "physfs",
            "SDL2",
            "SDL2main",
            "SDL2_net",
			"maps",
			"libmobile",
		}
		
		files {
			".\\**.c",
			".\\**.h",
		}

		removefiles {
			".\\lib\\libmobile\\**.c",
			".\\lib\\libmobile\\**.h",
			".\\lib\\pcg\\**.c",
			".\\lib\\pcg\\**.h",
			".\\maps\\**.c",
			".\\maps\\**.h",
			".\\test\\**.c",
			".\\test\\**.h",
			".\\engine\\battle\\move_effects\\**.c",
			".\\engine\\battle\\move_effects\\**.h",
		}
		
		newoption {
			trigger = "bugfix",
			description = "Force bugfixes"
		}

		newoption {
			trigger = "pcg",
			description = "Use PCG random number generator"
		}
		
		newoption {
			trigger = "fastbg",
			description = "Draws BG Map in single frame"
		}

		newoption {
			trigger = "physfs",
			description = "Use PhysFS for asset loading."
		}
		
		filter { "options:bugfix" }
			defines { "BUGFIX=1" }
		
		filter { "options:pcg" }
			defines { "ENHANCEMENT_USE_PCG=1" }
		
		filter { "options:fastbg" }
			defines { "ENHANCEMENT_DRAW_BG_IN_ONE_FRAME=1" }

		filter { "options:physfs" }
			defines { "USE_PHYSFS=1" }
			links { "physfs" }
		
		filter {}
		
		cdialect "gnu99"
		
		filter "system:Windows"
			files { "icon.rc" }
			cdialect "c99"

		filter {"system:Windows", "files:icon.rc" }
			buildcommands {
				"windres -i %{file.basename}.rc -o %{cfg.objdir}/%{file.basename}.o"
			}

			buildoutputs { 
				'%{cfg.objdir}/%{file.basename}.o'
			}
		
		filter {}

		flags
		{
			"NoRuntimeChecks",
			"MultiProcessorCompile"
		}