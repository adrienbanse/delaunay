# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build"

# Include any dependencies generated for this target.
include deps/BOV/CMakeFiles/bov.dir/depend.make

# Include the progress variables for this target.
include deps/BOV/CMakeFiles/bov.dir/progress.make

# Include the compile flags for this target's objects.
include deps/BOV/CMakeFiles/bov.dir/flags.make

deps/BOV/CMakeFiles/bov.dir/src/BOV.c.o: deps/BOV/CMakeFiles/bov.dir/flags.make
deps/BOV/CMakeFiles/bov.dir/src/BOV.c.o: ../deps/BOV/src/BOV.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/BOV/CMakeFiles/bov.dir/src/BOV.c.o"
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bov.dir/src/BOV.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/deps/BOV/src/BOV.c"

deps/BOV/CMakeFiles/bov.dir/src/BOV.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bov.dir/src/BOV.c.i"
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/deps/BOV/src/BOV.c" > CMakeFiles/bov.dir/src/BOV.c.i

deps/BOV/CMakeFiles/bov.dir/src/BOV.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bov.dir/src/BOV.c.s"
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/deps/BOV/src/BOV.c" -o CMakeFiles/bov.dir/src/BOV.c.s

# Object files for target bov
bov_OBJECTS = \
"CMakeFiles/bov.dir/src/BOV.c.o"

# External object files for target bov
bov_EXTERNAL_OBJECTS =

deps/BOV/lib/libbov.a: deps/BOV/CMakeFiles/bov.dir/src/BOV.c.o
deps/BOV/lib/libbov.a: deps/BOV/CMakeFiles/bov.dir/build.make
deps/BOV/lib/libbov.a: deps/BOV/CMakeFiles/bov.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library lib/libbov.a"
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && $(CMAKE_COMMAND) -P CMakeFiles/bov.dir/cmake_clean_target.cmake
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bov.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/BOV/CMakeFiles/bov.dir/build: deps/BOV/lib/libbov.a

.PHONY : deps/BOV/CMakeFiles/bov.dir/build

deps/BOV/CMakeFiles/bov.dir/clean:
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" && $(CMAKE_COMMAND) -P CMakeFiles/bov.dir/cmake_clean.cmake
.PHONY : deps/BOV/CMakeFiles/bov.dir/clean

deps/BOV/CMakeFiles/bov.dir/depend:
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/deps/BOV" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project_bis/build/deps/BOV/CMakeFiles/bov.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : deps/BOV/CMakeFiles/bov.dir/depend

