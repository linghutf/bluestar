# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linghutf/gitwork/bluestar/fanhao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linghutf/gitwork/bluestar/fanhao/build

# Include any dependencies generated for this target.
include CMakeFiles/mynote.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mynote.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mynote.dir/flags.make

CMakeFiles/mynote.dir/main.cc.o: CMakeFiles/mynote.dir/flags.make
CMakeFiles/mynote.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linghutf/gitwork/bluestar/fanhao/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mynote.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mynote.dir/main.cc.o -c /home/linghutf/gitwork/bluestar/fanhao/main.cc

CMakeFiles/mynote.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mynote.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linghutf/gitwork/bluestar/fanhao/main.cc > CMakeFiles/mynote.dir/main.cc.i

CMakeFiles/mynote.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mynote.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linghutf/gitwork/bluestar/fanhao/main.cc -o CMakeFiles/mynote.dir/main.cc.s

CMakeFiles/mynote.dir/main.cc.o.requires:

.PHONY : CMakeFiles/mynote.dir/main.cc.o.requires

CMakeFiles/mynote.dir/main.cc.o.provides: CMakeFiles/mynote.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/mynote.dir/build.make CMakeFiles/mynote.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/mynote.dir/main.cc.o.provides

CMakeFiles/mynote.dir/main.cc.o.provides.build: CMakeFiles/mynote.dir/main.cc.o


CMakeFiles/mynote.dir/handler.cc.o: CMakeFiles/mynote.dir/flags.make
CMakeFiles/mynote.dir/handler.cc.o: ../handler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linghutf/gitwork/bluestar/fanhao/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mynote.dir/handler.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mynote.dir/handler.cc.o -c /home/linghutf/gitwork/bluestar/fanhao/handler.cc

CMakeFiles/mynote.dir/handler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mynote.dir/handler.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linghutf/gitwork/bluestar/fanhao/handler.cc > CMakeFiles/mynote.dir/handler.cc.i

CMakeFiles/mynote.dir/handler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mynote.dir/handler.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linghutf/gitwork/bluestar/fanhao/handler.cc -o CMakeFiles/mynote.dir/handler.cc.s

CMakeFiles/mynote.dir/handler.cc.o.requires:

.PHONY : CMakeFiles/mynote.dir/handler.cc.o.requires

CMakeFiles/mynote.dir/handler.cc.o.provides: CMakeFiles/mynote.dir/handler.cc.o.requires
	$(MAKE) -f CMakeFiles/mynote.dir/build.make CMakeFiles/mynote.dir/handler.cc.o.provides.build
.PHONY : CMakeFiles/mynote.dir/handler.cc.o.provides

CMakeFiles/mynote.dir/handler.cc.o.provides.build: CMakeFiles/mynote.dir/handler.cc.o


# Object files for target mynote
mynote_OBJECTS = \
"CMakeFiles/mynote.dir/main.cc.o" \
"CMakeFiles/mynote.dir/handler.cc.o"

# External object files for target mynote
mynote_EXTERNAL_OBJECTS =

mynote: CMakeFiles/mynote.dir/main.cc.o
mynote: CMakeFiles/mynote.dir/handler.cc.o
mynote: CMakeFiles/mynote.dir/build.make
mynote: CMakeFiles/mynote.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linghutf/gitwork/bluestar/fanhao/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable mynote"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mynote.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mynote.dir/build: mynote

.PHONY : CMakeFiles/mynote.dir/build

CMakeFiles/mynote.dir/requires: CMakeFiles/mynote.dir/main.cc.o.requires
CMakeFiles/mynote.dir/requires: CMakeFiles/mynote.dir/handler.cc.o.requires

.PHONY : CMakeFiles/mynote.dir/requires

CMakeFiles/mynote.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mynote.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mynote.dir/clean

CMakeFiles/mynote.dir/depend:
	cd /home/linghutf/gitwork/bluestar/fanhao/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linghutf/gitwork/bluestar/fanhao /home/linghutf/gitwork/bluestar/fanhao /home/linghutf/gitwork/bluestar/fanhao/build /home/linghutf/gitwork/bluestar/fanhao/build /home/linghutf/gitwork/bluestar/fanhao/build/CMakeFiles/mynote.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mynote.dir/depend
