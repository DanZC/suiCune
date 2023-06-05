workspace "suiCune"
	location ".\\build\\"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	architecture "x86"
	warnings "extra"

	syslibdirs {
        ".\\deps\\SDL2\\lib\\x86\\"
	}

	includedirs {
		".\\src\\",
        ".\\deps\\SDL2\\include\\"
	}

	platforms {
		"x86",
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

	project "suiCune"
		targetname "suiCune"
		language "c++"
		kind "windowedapp"
		warnings "off"

		links {
            "SDL2",
            "SDL2main",
		}
		
		files {
			".\\**.c",
			".\\**.h",
		}