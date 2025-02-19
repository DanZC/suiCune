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
		optimize "debug"
		runtime "debug"
		symbols "on"

	filter "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"
		disablewarnings { ";4201;4102;4152;4200" }

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
			".\\maps\\**.c",
			".\\maps\\**.h",
			".\\test\\**.c",
			".\\test\\**.h",
			".\\engine\\battle\\move_effects\\**.c",
			".\\engine\\battle\\move_effects\\**.h",
		}
		
		cdialect "gnu99"
		
		filter "system:Windows"
			files { "icon.rc" }
			cdialect "c99"
			links { "ws2_32" }

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