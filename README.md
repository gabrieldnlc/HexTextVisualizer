# Description

![Animation3](https://user-images.githubusercontent.com/83305378/184227085-c13445db-64cf-40fa-8271-cfa741774fb1.gif)

A tool to help analyze text tables in Hex files. Created for the tables used by Konami on the Tag Force series, but can be used to read data laid out in a similar way.

Made with C++ and [Dear ImGui](https://github.com/ocornut/imgui) for Windows. Unit testing is powered by [Catch2](https://github.com/catchorg/Catch2/).

# Usage

-- TODO --

# Build instructions

HexTableVisualizer uses [Premake](https://github.com/premake/premake-core) to handle solution files. 

Run VS2022.bat to get an .sln file targeting Visual Studio 2022 or use the command line to run Premake passing the [desired target](https://premake.github.io/docs/Using-Premake/) as a parameter:

```Bash
$ cd premake/
$ premake5.exe --file=../premake5.lua <desired-target>
```

# Dependencies

For ease of use, all the dependencies files are already included in the repository.

| Library  | License |
| ------------- | ------------- |
| [Dear ImGui](https://github.com/ocornut/imgui)  | [MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)  |
| [TCLAP](http://tclap.sourceforge.net/) | [MIT](http://opensource.org/licenses/mit-license.php) |

-- TODO: INCORPORATES FONTS --

