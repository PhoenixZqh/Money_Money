if(EXISTS "/home/Money_Money/ROS/learn_gtest/build/demo3[1]_tests.cmake")
  include("/home/Money_Money/ROS/learn_gtest/build/demo3[1]_tests.cmake")
else()
  add_test(demo3_NOT_BUILT demo3_NOT_BUILT)
endif()