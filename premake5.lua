workspace "suiCune"
startproject "suiCune"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}"
	
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    buildlog  ("bin-obj/" .. outputdir .. "%{prj.name}.log")

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	architecture "x86"
	warnings "extra"

	syslibdirs {
        ".\\deps\\SDL2\\lib\\x86\\",
        ".\\deps\\physfs\\lib\\x86\\"
	}

	includedirs {
		".\\src\\",
        ".\\deps\\SDL2\\include\\",
        ".\\deps\\physfs\\include\\"
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
		language "c"
		kind "windowedapp"
		warnings "off"

		links {
            "physfs",
            "SDL2",
            "SDL2main",
            "SDL2_net",
		}
		
		files {
			".\\**.c",
			".\\**.h",
		}
		
		flags
		{
			"NoRuntimeChecks",
			"MultiProcessorCompile"
		}