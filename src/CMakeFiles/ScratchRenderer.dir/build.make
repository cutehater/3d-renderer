# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cutehater/3d-renderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cutehater/3d-renderer

# Include any dependencies generated for this target.
include src/CMakeFiles/ScratchRenderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/ScratchRenderer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ScratchRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ScratchRenderer.dir/flags.make

src/CMakeFiles/ScratchRenderer.dir/application.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/application.cpp.o: src/application.cpp
src/CMakeFiles/ScratchRenderer.dir/application.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/application.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/application.cpp.o -MF CMakeFiles/ScratchRenderer.dir/application.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/application.cpp.o -c /home/cutehater/3d-renderer/src/application.cpp

src/CMakeFiles/ScratchRenderer.dir/application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/application.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/application.cpp > CMakeFiles/ScratchRenderer.dir/application.cpp.i

src/CMakeFiles/ScratchRenderer.dir/application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/application.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/application.cpp -o CMakeFiles/ScratchRenderer.dir/application.cpp.s

src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o: src/camera.cpp
src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o -MF CMakeFiles/ScratchRenderer.dir/camera.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/camera.cpp.o -c /home/cutehater/3d-renderer/src/camera.cpp

src/CMakeFiles/ScratchRenderer.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/camera.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/camera.cpp > CMakeFiles/ScratchRenderer.dir/camera.cpp.i

src/CMakeFiles/ScratchRenderer.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/camera.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/camera.cpp -o CMakeFiles/ScratchRenderer.dir/camera.cpp.s

src/CMakeFiles/ScratchRenderer.dir/object.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/object.cpp.o: src/object.cpp
src/CMakeFiles/ScratchRenderer.dir/object.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/object.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/object.cpp.o -MF CMakeFiles/ScratchRenderer.dir/object.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/object.cpp.o -c /home/cutehater/3d-renderer/src/object.cpp

src/CMakeFiles/ScratchRenderer.dir/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/object.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/object.cpp > CMakeFiles/ScratchRenderer.dir/object.cpp.i

src/CMakeFiles/ScratchRenderer.dir/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/object.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/object.cpp -o CMakeFiles/ScratchRenderer.dir/object.cpp.s

src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o: src/off_loader.cpp
src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o -MF CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o -c /home/cutehater/3d-renderer/src/off_loader.cpp

src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/off_loader.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/off_loader.cpp > CMakeFiles/ScratchRenderer.dir/off_loader.cpp.i

src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/off_loader.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/off_loader.cpp -o CMakeFiles/ScratchRenderer.dir/off_loader.cpp.s

src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o: src/primitives.cpp
src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o -MF CMakeFiles/ScratchRenderer.dir/primitives.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/primitives.cpp.o -c /home/cutehater/3d-renderer/src/primitives.cpp

src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/primitives.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/primitives.cpp > CMakeFiles/ScratchRenderer.dir/primitives.cpp.i

src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/primitives.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/primitives.cpp -o CMakeFiles/ScratchRenderer.dir/primitives.cpp.s

src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o: src/renderer.cpp
src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o -MF CMakeFiles/ScratchRenderer.dir/renderer.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/renderer.cpp.o -c /home/cutehater/3d-renderer/src/renderer.cpp

src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/renderer.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/renderer.cpp > CMakeFiles/ScratchRenderer.dir/renderer.cpp.i

src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/renderer.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/renderer.cpp -o CMakeFiles/ScratchRenderer.dir/renderer.cpp.s

src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o: src/screen.cpp
src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o -MF CMakeFiles/ScratchRenderer.dir/screen.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/screen.cpp.o -c /home/cutehater/3d-renderer/src/screen.cpp

src/CMakeFiles/ScratchRenderer.dir/screen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/screen.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/screen.cpp > CMakeFiles/ScratchRenderer.dir/screen.cpp.i

src/CMakeFiles/ScratchRenderer.dir/screen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/screen.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/screen.cpp -o CMakeFiles/ScratchRenderer.dir/screen.cpp.s

src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o: src/vector4.cpp
src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o -MF CMakeFiles/ScratchRenderer.dir/vector4.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/vector4.cpp.o -c /home/cutehater/3d-renderer/src/vector4.cpp

src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/vector4.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/vector4.cpp > CMakeFiles/ScratchRenderer.dir/vector4.cpp.i

src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/vector4.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/vector4.cpp -o CMakeFiles/ScratchRenderer.dir/vector4.cpp.s

src/CMakeFiles/ScratchRenderer.dir/world.cpp.o: src/CMakeFiles/ScratchRenderer.dir/flags.make
src/CMakeFiles/ScratchRenderer.dir/world.cpp.o: src/world.cpp
src/CMakeFiles/ScratchRenderer.dir/world.cpp.o: src/CMakeFiles/ScratchRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/ScratchRenderer.dir/world.cpp.o"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/ScratchRenderer.dir/world.cpp.o -MF CMakeFiles/ScratchRenderer.dir/world.cpp.o.d -o CMakeFiles/ScratchRenderer.dir/world.cpp.o -c /home/cutehater/3d-renderer/src/world.cpp

src/CMakeFiles/ScratchRenderer.dir/world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScratchRenderer.dir/world.cpp.i"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cutehater/3d-renderer/src/world.cpp > CMakeFiles/ScratchRenderer.dir/world.cpp.i

src/CMakeFiles/ScratchRenderer.dir/world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScratchRenderer.dir/world.cpp.s"
	cd /home/cutehater/3d-renderer/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cutehater/3d-renderer/src/world.cpp -o CMakeFiles/ScratchRenderer.dir/world.cpp.s

# Object files for target ScratchRenderer
ScratchRenderer_OBJECTS = \
"CMakeFiles/ScratchRenderer.dir/application.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/camera.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/object.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/primitives.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/renderer.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/screen.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/vector4.cpp.o" \
"CMakeFiles/ScratchRenderer.dir/world.cpp.o"

# External object files for target ScratchRenderer
ScratchRenderer_EXTERNAL_OBJECTS =

src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/application.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/camera.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/object.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/off_loader.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/primitives.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/renderer.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/screen.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/vector4.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/world.cpp.o
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/build.make
src/libScratchRenderer.a: src/CMakeFiles/ScratchRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cutehater/3d-renderer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libScratchRenderer.a"
	cd /home/cutehater/3d-renderer/src && $(CMAKE_COMMAND) -P CMakeFiles/ScratchRenderer.dir/cmake_clean_target.cmake
	cd /home/cutehater/3d-renderer/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScratchRenderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/ScratchRenderer.dir/build: src/libScratchRenderer.a
.PHONY : src/CMakeFiles/ScratchRenderer.dir/build

src/CMakeFiles/ScratchRenderer.dir/clean:
	cd /home/cutehater/3d-renderer/src && $(CMAKE_COMMAND) -P CMakeFiles/ScratchRenderer.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ScratchRenderer.dir/clean

src/CMakeFiles/ScratchRenderer.dir/depend:
	cd /home/cutehater/3d-renderer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cutehater/3d-renderer /home/cutehater/3d-renderer/src /home/cutehater/3d-renderer /home/cutehater/3d-renderer/src /home/cutehater/3d-renderer/src/CMakeFiles/ScratchRenderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/ScratchRenderer.dir/depend
