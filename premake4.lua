
CHIPMUNK_ROOT = CHIPMUNK_ROOT or ""

project "CppChipmunk"
	kind "StaticLib"
	configurations {"Debug", "Release"}
	includedirs {
		"include",
		path.join(CHIPMUNK_ROOT, "include/chipmunk")
	}
	files {"src/**.cpp", "include/**.hpp"}

	libdirs {
		"../Chipmunk-6.1.1/src"
	}

	targetdir "bin"

	configuration"Debug"
		targetname"CppChipmunk_d"

	links {
		"chipmunk_d"
	}
	configuration"Release"
		targetname"CppChipmunk"
	links {
		"chipmunk"
	}