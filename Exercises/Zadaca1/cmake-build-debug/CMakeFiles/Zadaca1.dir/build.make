# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Zadaca1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Zadaca1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Zadaca1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Zadaca1.dir/flags.make

CMakeFiles/Zadaca1.dir/main.cpp.obj: CMakeFiles/Zadaca1.dir/flags.make
CMakeFiles/Zadaca1.dir/main.cpp.obj: C:/Users/Borjan/Desktop/Object_Oriented_Programing_cpp/Exercises/Zadaca1/main.cpp
CMakeFiles/Zadaca1.dir/main.cpp.obj: CMakeFiles/Zadaca1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Zadaca1.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Zadaca1.dir/main.cpp.obj -MF CMakeFiles\Zadaca1.dir\main.cpp.obj.d -o CMakeFiles\Zadaca1.dir\main.cpp.obj -c C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\main.cpp

CMakeFiles/Zadaca1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Zadaca1.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\main.cpp > CMakeFiles\Zadaca1.dir\main.cpp.i

CMakeFiles/Zadaca1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Zadaca1.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\main.cpp -o CMakeFiles\Zadaca1.dir\main.cpp.s

# Object files for target Zadaca1
Zadaca1_OBJECTS = \
"CMakeFiles/Zadaca1.dir/main.cpp.obj"

# External object files for target Zadaca1
Zadaca1_EXTERNAL_OBJECTS =

Zadaca1.exe: CMakeFiles/Zadaca1.dir/main.cpp.obj
Zadaca1.exe: CMakeFiles/Zadaca1.dir/build.make
Zadaca1.exe: CMakeFiles/Zadaca1.dir/linkLibs.rsp
Zadaca1.exe: CMakeFiles/Zadaca1.dir/objects1.rsp
Zadaca1.exe: CMakeFiles/Zadaca1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Zadaca1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Zadaca1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Zadaca1.dir/build: Zadaca1.exe
.PHONY : CMakeFiles/Zadaca1.dir/build

CMakeFiles/Zadaca1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Zadaca1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Zadaca1.dir/clean

CMakeFiles/Zadaca1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1 C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1 C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug C:\Users\Borjan\Desktop\Object_Oriented_Programing_cpp\Exercises\Zadaca1\cmake-build-debug\CMakeFiles\Zadaca1.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Zadaca1.dir/depend

