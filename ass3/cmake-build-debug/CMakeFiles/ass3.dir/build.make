# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Schule\CLionProjects\Solitaer_C\ass3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\ass3.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\ass3.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\ass3.dir\flags.make

CMakeFiles\ass3.dir\ass3.c.obj: CMakeFiles\ass3.dir\flags.make
CMakeFiles\ass3.dir\ass3.c.obj: ..\ass3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ass3.dir/ass3.c.obj"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\ass3.dir\ass3.c.obj /FdCMakeFiles\ass3.dir\ /FS -c C:\Users\Schule\CLionProjects\Solitaer_C\ass3\ass3.c
<<

CMakeFiles\ass3.dir\ass3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ass3.dir/ass3.c.i"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe > CMakeFiles\ass3.dir\ass3.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Schule\CLionProjects\Solitaer_C\ass3\ass3.c
<<

CMakeFiles\ass3.dir\ass3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ass3.dir/ass3.c.s"
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\ass3.dir\ass3.c.s /c C:\Users\Schule\CLionProjects\Solitaer_C\ass3\ass3.c
<<

# Object files for target ass3
ass3_OBJECTS = \
"CMakeFiles\ass3.dir\ass3.c.obj"

# External object files for target ass3
ass3_EXTERNAL_OBJECTS =

ass3.exe: CMakeFiles\ass3.dir\ass3.c.obj
ass3.exe: CMakeFiles\ass3.dir\build.make
ass3.exe: CMakeFiles\ass3.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ass3.exe"
	"C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ass3.dir --manifests  -- C:\PROGRA~2\MICROS~1.0\VC\bin\link.exe /nologo @CMakeFiles\ass3.dir\objects1.rsp @<<
 /out:ass3.exe /implib:ass3.lib /pdb:C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug\ass3.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\ass3.dir\build: ass3.exe

.PHONY : CMakeFiles\ass3.dir\build

CMakeFiles\ass3.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ass3.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ass3.dir\clean

CMakeFiles\ass3.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Schule\CLionProjects\Solitaer_C\ass3 C:\Users\Schule\CLionProjects\Solitaer_C\ass3 C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug C:\Users\Schule\CLionProjects\Solitaer_C\ass3\cmake-build-debug\CMakeFiles\ass3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\ass3.dir\depend

