# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/clion/305/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/305/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MidProjectMugnaiLorenzo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MidProjectMugnaiLorenzo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make

CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/main.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/main.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/main.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/main.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.s

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/ParallelSoA.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/ParallelSoA.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/ParallelSoA.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/ParallelSoA.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.s

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/SequentialSoA.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/SequentialSoA.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/SequentialSoA.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/SoA/SequentialSoA.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.s

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/ParallelAoS.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/ParallelAoS.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/ParallelAoS.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/ParallelAoS.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.s

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/SequentialAoS.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/SequentialAoS.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/SequentialAoS.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/SequentialAoS.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.s

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/flags.make
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o: /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/Ngram.cpp
CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o: CMakeFiles/MidProjectMugnaiLorenzo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o -MF CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o.d -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o -c /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/Ngram.cpp

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/Ngram.cpp > CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.i

CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/AoS/Ngram.cpp -o CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.s

# Object files for target MidProjectMugnaiLorenzo
MidProjectMugnaiLorenzo_OBJECTS = \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o" \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o" \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o" \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o" \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o" \
"CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o"

# External object files for target MidProjectMugnaiLorenzo
MidProjectMugnaiLorenzo_EXTERNAL_OBJECTS =

MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/main.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/ParallelSoA.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/SoA/SequentialSoA.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/ParallelAoS.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/SequentialAoS.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/AoS/Ngram.cpp.o
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/build.make
MidProjectMugnaiLorenzo: /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.so
MidProjectMugnaiLorenzo: /usr/lib/x86_64-linux-gnu/libpthread.a
MidProjectMugnaiLorenzo: CMakeFiles/MidProjectMugnaiLorenzo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable MidProjectMugnaiLorenzo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MidProjectMugnaiLorenzo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MidProjectMugnaiLorenzo.dir/build: MidProjectMugnaiLorenzo
.PHONY : CMakeFiles/MidProjectMugnaiLorenzo.dir/build

CMakeFiles/MidProjectMugnaiLorenzo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MidProjectMugnaiLorenzo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MidProjectMugnaiLorenzo.dir/clean

CMakeFiles/MidProjectMugnaiLorenzo.dir/depend:
	cd /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug /home/lorenzo/CLionProjects/MidProjectMugnaiLorenzo/cmake-build-debug/CMakeFiles/MidProjectMugnaiLorenzo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MidProjectMugnaiLorenzo.dir/depend

