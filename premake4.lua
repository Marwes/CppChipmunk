
CHIPMUNK_ROOT = CHIPMUNK_ROOT or ""

project "CppChipmunk"
	kind "StaticLib"
	configurations {"Debug", "Release"}
	includedirs {
		path.join(CHIPMUNK_ROOT, "include/chipmunk")
	}

	files {"**.cpp", "**.hpp"}

	configuration"Debug"
		targetname"CppChipmunk_d"

	configuration"Release"
		targetname"CppChipmunk"
