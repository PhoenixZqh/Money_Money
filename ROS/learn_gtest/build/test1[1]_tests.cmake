add_test([=[FooTest.HandleNoneZeroInput]=]  /home/Money_Money/ROS/learn_gtest/build/devel/lib/learn_gtest/test1 [==[--gtest_filter=FooTest.HandleNoneZeroInput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FooTest.HandleNoneZeroInput]=]  PROPERTIES WORKING_DIRECTORY /home/Money_Money/ROS/learn_gtest/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  test1_TESTS FooTest.HandleNoneZeroInput)
