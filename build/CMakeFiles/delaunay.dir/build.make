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
CMAKE_SOURCE_DIR = "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build"

# Include any dependencies generated for this target.
include CMakeFiles/delaunay.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/delaunay.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/delaunay.dir/flags.make

CMakeFiles/delaunay.dir/src/main.c.o: CMakeFiles/delaunay.dir/flags.make
CMakeFiles/delaunay.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/delaunay.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/delaunay.dir/src/main.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/main.c"

CMakeFiles/delaunay.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/delaunay.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/main.c" > CMakeFiles/delaunay.dir/src/main.c.i

CMakeFiles/delaunay.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/delaunay.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/main.c" -o CMakeFiles/delaunay.dir/src/main.c.s

CMakeFiles/delaunay.dir/src/inputs.c.o: CMakeFiles/delaunay.dir/flags.make
CMakeFiles/delaunay.dir/src/inputs.c.o: ../src/inputs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/delaunay.dir/src/inputs.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/delaunay.dir/src/inputs.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/inputs.c"

CMakeFiles/delaunay.dir/src/inputs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/delaunay.dir/src/inputs.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/inputs.c" > CMakeFiles/delaunay.dir/src/inputs.c.i

CMakeFiles/delaunay.dir/src/inputs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/delaunay.dir/src/inputs.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/inputs.c" -o CMakeFiles/delaunay.dir/src/inputs.c.s

CMakeFiles/delaunay.dir/src/mesh.c.o: CMakeFiles/delaunay.dir/flags.make
CMakeFiles/delaunay.dir/src/mesh.c.o: ../src/mesh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/delaunay.dir/src/mesh.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/delaunay.dir/src/mesh.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/mesh.c"

CMakeFiles/delaunay.dir/src/mesh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/delaunay.dir/src/mesh.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/mesh.c" > CMakeFiles/delaunay.dir/src/mesh.c.i

CMakeFiles/delaunay.dir/src/mesh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/delaunay.dir/src/mesh.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/mesh.c" -o CMakeFiles/delaunay.dir/src/mesh.c.s

CMakeFiles/delaunay.dir/src/delaunay.c.o: CMakeFiles/delaunay.dir/flags.make
CMakeFiles/delaunay.dir/src/delaunay.c.o: ../src/delaunay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/delaunay.dir/src/delaunay.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/delaunay.dir/src/delaunay.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/delaunay.c"

CMakeFiles/delaunay.dir/src/delaunay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/delaunay.dir/src/delaunay.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/delaunay.c" > CMakeFiles/delaunay.dir/src/delaunay.c.i

CMakeFiles/delaunay.dir/src/delaunay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/delaunay.dir/src/delaunay.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/delaunay.c" -o CMakeFiles/delaunay.dir/src/delaunay.c.s

CMakeFiles/delaunay.dir/src/visualize.c.o: CMakeFiles/delaunay.dir/flags.make
CMakeFiles/delaunay.dir/src/visualize.c.o: ../src/visualize.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/delaunay.dir/src/visualize.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/delaunay.dir/src/visualize.c.o   -c "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/visualize.c"

CMakeFiles/delaunay.dir/src/visualize.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/delaunay.dir/src/visualize.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/visualize.c" > CMakeFiles/delaunay.dir/src/visualize.c.i

CMakeFiles/delaunay.dir/src/visualize.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/delaunay.dir/src/visualize.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/src/visualize.c" -o CMakeFiles/delaunay.dir/src/visualize.c.s

# Object files for target delaunay
delaunay_OBJECTS = \
"CMakeFiles/delaunay.dir/src/main.c.o" \
"CMakeFiles/delaunay.dir/src/inputs.c.o" \
"CMakeFiles/delaunay.dir/src/mesh.c.o" \
"CMakeFiles/delaunay.dir/src/delaunay.c.o" \
"CMakeFiles/delaunay.dir/src/visualize.c.o"

# External object files for target delaunay
delaunay_EXTERNAL_OBJECTS =

bin/delaunay: CMakeFiles/delaunay.dir/src/main.c.o
bin/delaunay: CMakeFiles/delaunay.dir/src/inputs.c.o
bin/delaunay: CMakeFiles/delaunay.dir/src/mesh.c.o
bin/delaunay: CMakeFiles/delaunay.dir/src/delaunay.c.o
bin/delaunay: CMakeFiles/delaunay.dir/src/visualize.c.o
bin/delaunay: CMakeFiles/delaunay.dir/build.make
bin/delaunay: deps/BOV/lib/libbov.a
bin/delaunay: deps/BOV/deps/glad/libglad.a
bin/delaunay: deps/BOV/deps/glfw/src/libglfw3.a
bin/delaunay: CMakeFiles/delaunay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable bin/delaunay"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/delaunay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/delaunay.dir/build: bin/delaunay

.PHONY : CMakeFiles/delaunay.dir/build

CMakeFiles/delaunay.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/delaunay.dir/cmake_clean.cmake
.PHONY : CMakeFiles/delaunay.dir/clean

CMakeFiles/delaunay.dir/depend:
	cd "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build" "/Users/adrienbanse/OneDrive - UCL/MASTER/Q9/LMECA2170/LMECA2170_project/build/CMakeFiles/delaunay.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/delaunay.dir/depend

