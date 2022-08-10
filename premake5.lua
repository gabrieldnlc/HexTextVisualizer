main_project = "HexTextVisualizer"

workspace (main_project)
	startproject (main_project)
	architecture "x86"
	configurations{
		"Debug",
		"Release"
	}
	platforms{ 
		"Win32"
	}

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
target_dir = ("bin/" .. output_dir .. "/%{prj.name}")

project (main_project)
	location (main_project)
	kind "ConsoleApp"
	language "C++"
	defines{"IMGUI_DEFINE_MATH_OPERATORS"}
	
	targetdir (target_dir)
	objdir ("bin-int/" .. output_dir .. "/%{prj.name}")
	debugdir ("bin/" .. output_dir .. "/%{prj.name}")

	postbuildcommands {
		("{COPY} extern/SDL2/lib/x86/SDL2.dll ../" .. target_dir .. "/"),
	}

	files{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/extern/imgui/imgui.cpp",
		"%{prj.name}/extern/imgui/imgui_draw.cpp",
		"%{prj.name}/extern/imgui/imgui_widgets.cpp",
		"%{prj.name}/extern/imgui/imgui_tables.cpp",
		"%{prj.name}/extern/imgui/backends/imgui_impl_dx11.cpp",
		"%{prj.name}/extern/imgui/backends/imgui_impl_sdl.cpp",
		"%{prj.name}/extern/imgui/imgui_demo.cpp",
		"%{prj.name}/extern/imgui/misc/cpp/imgui_stdlib.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/extern/SDL2/include",
		"%{prj.name}/extern/imgui/",
		"%{prj.name}/extern/imgui/backends",
		"%{prj.name}/extern/imgui/misc/cpp",
		"%{prj.name}/extern/TCLAP/include",
	}
	libdirs{
		"%{prj.name}/extern/SDL2/lib/x86",
	}
	
	links{
		"SDL2.lib",
		"SDL2main.lib",
		"d3d11.lib",
		"d3dcompiler.lib",
		"dxgi.lib",
	}

	filter "system:windows"
		cppdialect "C++latest"
		systemversion "latest"

		defines{
			"WIN32",
		}

		filter "platforms:x86"
        	system "Windows"
        	architecture "x86"

		filter "configurations:Debug"
			defines "HEX_DEBUG"
			symbols "On"
			runtime "Debug"
			libdirs{
				--
			}
			links{
				--
			}

		filter "configurations:Release"
			defines "HEX_RELEASE"
			optimize "On"
			runtime "Release"
			libdirs{
				--
			}
			links{
				--
			}

project "Tests"
	location "Tests"
	kind "ConsoleApp"
	language "C++"

	targetdir (target_dir)
	objdir ("bin-int/" .. output_dir .. "/%{prj.name}")
	debugdir ("bin/" .. output_dir .. "/%{prj.name}")

	postbuildcommands {
		--,
	}

	links { (main_project) }
	files{
		"%{prj.name}/**.cpp",

	}
	includedirs{
		"%{prj.name}/Catch2/",
		(main_project) .. "/src/",
	}
	libdirs{
		"bin-int/" .. output_dir .. "/" .. (main_project),
	}

	filter "system:windows"
		cppdialect "C++latest"
		systemversion "latest"

		defines{
			"WIN32",
		}

		filter "platforms:x86"
        	system "Windows"
        	architecture "x86"

		filter "configurations:Debug"
			defines "HEX_DEBUG"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			defines "HEX_RELEASE"
			optimize "On"
			runtime "Release"