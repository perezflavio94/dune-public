# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build

# Include any dependencies generated for this target.
include CMakeFiles/static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/static.dir/flags.make

ui_static.h: ../ui/static.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_static.h"
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic -o /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/ui_static.h /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/ui/static.ui

CMakeFiles/static.dir/src/Static.cpp.o: CMakeFiles/static.dir/flags.make
CMakeFiles/static.dir/src/Static.cpp.o: ../src/Static.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/static.dir/src/Static.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/static.dir/src/Static.cpp.o -c /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/Static.cpp

CMakeFiles/static.dir/src/Static.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/static.dir/src/Static.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/Static.cpp > CMakeFiles/static.dir/src/Static.cpp.i

CMakeFiles/static.dir/src/Static.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/static.dir/src/Static.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/Static.cpp -o CMakeFiles/static.dir/src/Static.cpp.s

CMakeFiles/static.dir/src/main.cpp.o: CMakeFiles/static.dir/flags.make
CMakeFiles/static.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/static.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/static.dir/src/main.cpp.o -c /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/main.cpp

CMakeFiles/static.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/static.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/main.cpp > CMakeFiles/static.dir/src/main.cpp.i

CMakeFiles/static.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/static.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/src/main.cpp -o CMakeFiles/static.dir/src/main.cpp.s

# Object files for target static
static_OBJECTS = \
"CMakeFiles/static.dir/src/Static.cpp.o" \
"CMakeFiles/static.dir/src/main.cpp.o"

# External object files for target static
static_EXTERNAL_OBJECTS =

static: CMakeFiles/static.dir/src/Static.cpp.o
static: CMakeFiles/static.dir/src/main.cpp.o
static: CMakeFiles/static.dir/build.make
static: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.5.1
static: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.5.1
static: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.5.1
static: CMakeFiles/static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable static"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/static.dir/build: static

.PHONY : CMakeFiles/static.dir/build

CMakeFiles/static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/static.dir/clean

CMakeFiles/static.dir/depend: ui_static.h
	cd /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build /home/emiliano/fiuba/7542-Taller/tp4-dune/static-image/build/CMakeFiles/static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/static.dir/depend

