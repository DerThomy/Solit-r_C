# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Simon\CLionProjects\Solitaer_C\ass3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ass3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ass3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ass3.dir/flags.make

CMakeFiles/ass3.dir/ass3.c.obj: CMakeFiles/ass3.dir/flags.make
CMakeFiles/ass3.dir/ass3.c.obj: ../ass3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ass3.dir/ass3.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ass3.dir\ass3.c.obj   -c C:\Users\Simon\CLionProjects\Solitaer_C\ass3\ass3.c

CMakeFiles/ass3.dir/ass3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ass3.dir/ass3.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Simon\CLionProjects\Solitaer_C\ass3\ass3.c > CMakeFiles\ass3.dir\ass3.c.i

CMakeFiles/ass3.dir/ass3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ass3.dir/ass3.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Simon\CLionProjects\Solitaer_C\ass3\ass3.c -o CMakeFiles\ass3.dir\ass3.c.s

# Object files for target ass3
ass3_OBJECTS = \
"CMakeFiles/ass3.dir/ass3.c.obj"

# External object files for target ass3
ass3_EXTERNAL_OBJECTS =

ass3.exe: CMakeFiles/ass3.dir/ass3.c.obj
ass3.exe: CMakeFiles/ass3.dir/build.make
ass3.exe: CMakeFiles/ass3.dir/linklibs.rsp
ass3.exe: CMakeFiles/ass3.dir/objects1.rsp
ass3.exe: CMakeFiles/ass3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ass3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ass3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ass3.dir/build: ass3.exe

.PHONY : CMakeFiles/ass3.dir/build

CMakeFiles/ass3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ass3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ass3.dir/clean

CMakeFiles/ass3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Simon\CLionProjects\Solitaer_C\ass3 C:\Users\Simon\CLionProjects\Solitaer_C\ass3 C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug C:\Users\Simon\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles\ass3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ass3.dir/depend

