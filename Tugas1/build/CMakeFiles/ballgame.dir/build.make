# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/necloid/Tugas1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/necloid/Tugas1/build

# Include any dependencies generated for this target.
include CMakeFiles/ballgame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ballgame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ballgame.dir/flags.make

CMakeFiles/ballgame.dir/src/main.cpp.o: CMakeFiles/ballgame.dir/flags.make
CMakeFiles/ballgame.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/necloid/Tugas1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ballgame.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ballgame.dir/src/main.cpp.o -c /home/necloid/Tugas1/src/main.cpp

CMakeFiles/ballgame.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ballgame.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/necloid/Tugas1/src/main.cpp > CMakeFiles/ballgame.dir/src/main.cpp.i

CMakeFiles/ballgame.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ballgame.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/necloid/Tugas1/src/main.cpp -o CMakeFiles/ballgame.dir/src/main.cpp.s

# Object files for target ballgame
ballgame_OBJECTS = \
"CMakeFiles/ballgame.dir/src/main.cpp.o"

# External object files for target ballgame
ballgame_EXTERNAL_OBJECTS =

ballgame: CMakeFiles/ballgame.dir/src/main.cpp.o
ballgame: CMakeFiles/ballgame.dir/build.make
ballgame: /usr/local/lib/libopencv_gapi.so.4.10.0
ballgame: /usr/local/lib/libopencv_highgui.so.4.10.0
ballgame: /usr/local/lib/libopencv_ml.so.4.10.0
ballgame: /usr/local/lib/libopencv_objdetect.so.4.10.0
ballgame: /usr/local/lib/libopencv_photo.so.4.10.0
ballgame: /usr/local/lib/libopencv_stitching.so.4.10.0
ballgame: /usr/local/lib/libopencv_video.so.4.10.0
ballgame: /usr/local/lib/libopencv_videoio.so.4.10.0
ballgame: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
ballgame: /usr/local/lib/libopencv_dnn.so.4.10.0
ballgame: /usr/local/lib/libopencv_calib3d.so.4.10.0
ballgame: /usr/local/lib/libopencv_features2d.so.4.10.0
ballgame: /usr/local/lib/libopencv_flann.so.4.10.0
ballgame: /usr/local/lib/libopencv_imgproc.so.4.10.0
ballgame: /usr/local/lib/libopencv_core.so.4.10.0
ballgame: CMakeFiles/ballgame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/necloid/Tugas1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ballgame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ballgame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ballgame.dir/build: ballgame

.PHONY : CMakeFiles/ballgame.dir/build

CMakeFiles/ballgame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ballgame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ballgame.dir/clean

CMakeFiles/ballgame.dir/depend:
	cd /home/necloid/Tugas1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/necloid/Tugas1 /home/necloid/Tugas1 /home/necloid/Tugas1/build /home/necloid/Tugas1/build /home/necloid/Tugas1/build/CMakeFiles/ballgame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ballgame.dir/depend

