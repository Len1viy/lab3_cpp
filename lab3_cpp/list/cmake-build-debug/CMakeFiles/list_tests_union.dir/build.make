# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /tmp/tmp.dlSuVIRW4O/list

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.dlSuVIRW4O/list/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/list_tests_union.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/list_tests_union.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/list_tests_union.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list_tests_union.dir/flags.make

CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o: CMakeFiles/list_tests_union.dir/flags.make
CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o: /tmp/tmp.dlSuVIRW4O/list/test/ListTests.cpp
CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o: CMakeFiles/list_tests_union.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/tmp/tmp.dlSuVIRW4O/list/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o -MF CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o.d -o CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o -c /tmp/tmp.dlSuVIRW4O/list/test/ListTests.cpp

CMakeFiles/list_tests_union.dir/test/ListTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/list_tests_union.dir/test/ListTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.dlSuVIRW4O/list/test/ListTests.cpp > CMakeFiles/list_tests_union.dir/test/ListTests.cpp.i

CMakeFiles/list_tests_union.dir/test/ListTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/list_tests_union.dir/test/ListTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.dlSuVIRW4O/list/test/ListTests.cpp -o CMakeFiles/list_tests_union.dir/test/ListTests.cpp.s

# Object files for target list_tests_union
list_tests_union_OBJECTS = \
"CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o"

# External object files for target list_tests_union
list_tests_union_EXTERNAL_OBJECTS =

list_tests_union: CMakeFiles/list_tests_union.dir/test/ListTests.cpp.o
list_tests_union: CMakeFiles/list_tests_union.dir/build.make
list_tests_union: CMakeFiles/list_tests_union.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/tmp/tmp.dlSuVIRW4O/list/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable list_tests_union"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list_tests_union.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list_tests_union.dir/build: list_tests_union
.PHONY : CMakeFiles/list_tests_union.dir/build

CMakeFiles/list_tests_union.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list_tests_union.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list_tests_union.dir/clean

CMakeFiles/list_tests_union.dir/depend:
	cd /tmp/tmp.dlSuVIRW4O/list/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.dlSuVIRW4O/list /tmp/tmp.dlSuVIRW4O/list /tmp/tmp.dlSuVIRW4O/list/cmake-build-debug /tmp/tmp.dlSuVIRW4O/list/cmake-build-debug /tmp/tmp.dlSuVIRW4O/list/cmake-build-debug/CMakeFiles/list_tests_union.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/list_tests_union.dir/depend

