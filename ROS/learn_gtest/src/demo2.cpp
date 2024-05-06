#include <gtest/gtest.h>

/**
 @brief 多组案例测试， 需要对gtest进行初始化
*/

int Factorial(int n)
{
    // printf("Running func() from %s\n", __func__);

    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

TEST(FactorialTest, Negative)
{
    EXPECT_EQ(1, Factorial(-5));
    EXPECT_EQ(1, Factorial(-1));
    EXPECT_GT(Factorial(-10), 0);
}
// 0
TEST(FactorialTest, Zero)
{
    EXPECT_EQ(0, Factorial(0)); // 给出错误案例
}
// 负数为一组
TEST(FactorialTest, Positive)
{
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(5, Factorial(3)); //给出错误案例
    EXPECT_EQ(40320, Factorial(8));
}

int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);

    testing::InitGoogleTest(&argc, argv); //需要初始化
    return RUN_ALL_TESTS();               //运行所有的test
}