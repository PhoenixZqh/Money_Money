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
CMAKE_SOURCE_DIR = /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build

# Include any dependencies generated for this target.
include cudaStudy/CMakeFiles/trt.dir/depend.make

# Include the progress variables for this target.
include cudaStudy/CMakeFiles/trt.dir/progress.make

# Include the compile flags for this target's objects.
include cudaStudy/CMakeFiles/trt.dir/flags.make

cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.o: cudaStudy/CMakeFiles/trt.dir/flags.make
cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.o: /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/src/affine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.o"
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trt.dir/src/affine.cpp.o -c /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/src/affine.cpp

cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trt.dir/src/affine.cpp.i"
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/src/affine.cpp > CMakeFiles/trt.dir/src/affine.cpp.i

cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trt.dir/src/affine.cpp.s"
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/src/affine.cpp -o CMakeFiles/trt.dir/src/affine.cpp.s

# Object files for target trt
trt_OBJECTS = \
"CMakeFiles/trt.dir/src/affine.cpp.o"

# External object files for target trt
trt_EXTERNAL_OBJECTS =

/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/devel/lib/libtrt.so: cudaStudy/CMakeFiles/trt.dir/src/affine.cpp.o
/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/devel/lib/libtrt.so: cudaStudy/CMakeFiles/trt.dir/build.make
/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/devel/lib/libtrt.so: cudaStudy/CMakeFiles/trt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/devel/lib/libtrt.so"
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cudaStudy/CMakeFiles/trt.dir/build: /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/devel/lib/libtrt.so

.PHONY : cudaStudy/CMakeFiles/trt.dir/build

cudaStudy/CMakeFiles/trt.dir/clean:
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy && $(CMAKE_COMMAND) -P CMakeFiles/trt.dir/cmake_clean.cmake
.PHONY : cudaStudy/CMakeFiles/trt.dir/clean

cudaStudy/CMakeFiles/trt.dir/depend:
	cd /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy /home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/build/cudaStudy/CMakeFiles/trt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cudaStudy/CMakeFiles/trt.dir/depend

