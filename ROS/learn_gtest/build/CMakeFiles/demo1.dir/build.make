# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Money_Money/ROS/learn_gtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Money_Money/ROS/learn_gtest/build

# Include any dependencies generated for this target.
include CMakeFiles/demo1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo1.dir/flags.make

CMakeFiles/demo1.dir/src/demo1.cpp.o: CMakeFiles/demo1.dir/flags.make
CMakeFiles/demo1.dir/src/demo1.cpp.o: ../src/demo1.cpp
CMakeFiles/demo1.dir/src/demo1.cpp.o: CMakeFiles/demo1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Money_Money/ROS/learn_gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo1.dir/src/demo1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo1.dir/src/demo1.cpp.o -MF CMakeFiles/demo1.dir/src/demo1.cpp.o.d -o CMakeFiles/demo1.dir/src/demo1.cpp.o -c /home/Money_Money/ROS/learn_gtest/src/demo1.cpp

CMakeFiles/demo1.dir/src/demo1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo1.dir/src/demo1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Money_Money/ROS/learn_gtest/src/demo1.cpp > CMakeFiles/demo1.dir/src/demo1.cpp.i

CMakeFiles/demo1.dir/src/demo1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo1.dir/src/demo1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Money_Money/ROS/learn_gtest/src/demo1.cpp -o CMakeFiles/demo1.dir/src/demo1.cpp.s

# Object files for target demo1
demo1_OBJECTS = \
"CMakeFiles/demo1.dir/src/demo1.cpp.o"

# External object files for target demo1
demo1_EXTERNAL_OBJECTS =

devel/lib/learn_gtest/demo1: CMakeFiles/demo1.dir/src/demo1.cpp.o
devel/lib/learn_gtest/demo1: CMakeFiles/demo1.dir/build.make
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_gapi.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_stitching.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_aruco.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_barcode.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_dpm.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_face.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_freetype.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_hfs.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_mcc.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_quality.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_rapid.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_reg.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_saliency.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_stereo.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_superres.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_tracking.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_videostab.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_xfeatures2d.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.5.5
devel/lib/learn_gtest/demo1: lib/libgtest_main.so.1.14.0
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_shape.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_datasets.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_plot.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_text.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_ml.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_optflow.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_video.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_dnn.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_features2d.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_flann.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_photo.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.5
devel/lib/learn_gtest/demo1: /usr/local/lib/x86_64-linux-gnu/libopencv_core.so.4.5.5
devel/lib/learn_gtest/demo1: lib/libgtest.so.1.14.0
devel/lib/learn_gtest/demo1: CMakeFiles/demo1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Money_Money/ROS/learn_gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable devel/lib/learn_gtest/demo1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo1.dir/link.txt --verbose=$(VERBOSE)
	/usr/local/bin/cmake -D TEST_TARGET=demo1 -D TEST_EXECUTABLE=/home/Money_Money/ROS/learn_gtest/build/devel/lib/learn_gtest/demo1 -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/Money_Money/ROS/learn_gtest/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=demo1_TESTS -D CTEST_FILE=/home/Money_Money/ROS/learn_gtest/build/demo1[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/local/share/cmake-3.23/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/demo1.dir/build: devel/lib/learn_gtest/demo1
.PHONY : CMakeFiles/demo1.dir/build

CMakeFiles/demo1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo1.dir/clean

CMakeFiles/demo1.dir/depend:
	cd /home/Money_Money/ROS/learn_gtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Money_Money/ROS/learn_gtest /home/Money_Money/ROS/learn_gtest /home/Money_Money/ROS/learn_gtest/build /home/Money_Money/ROS/learn_gtest/build /home/Money_Money/ROS/learn_gtest/build/CMakeFiles/demo1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo1.dir/depend

