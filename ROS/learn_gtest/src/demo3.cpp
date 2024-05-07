#include <iostream>
#include <gtest/gtest.h>
#include <memory>

/**
 * @brief 单元测试类
 * * TEST宏
 *   1. 定义一个独立的测试用例，该测试用例不依赖特定的测试夹具
 *   2. 测试用例的名称通常包含一个描述测试的函数或功能的字符串
 *   3. 每个测试用例都在自己的测试环境中运行
 * * TEST_F宏
 *   1. 定义基于测试夹具的测试用例，可访问夹具中的成员变量和方法
 *   2. 提供夹具类的名称作为第一个参数
 *   3. 该种测试用例可以共享相同的测试环境，避免重复的初始化和销毁
*/

class CALC
{
private:
    /* data */
public:
    CALC(/* args */) = default;
    ~CALC() = default;

    int Add(int a, int b)
    {
        return a + b;
    }

    int Minus(int a, int b)
    {
        return a - b;
    }

    int Multi(int a, int b)
    {
        return a * b;
    }

    float Divide(float a, float b)
    {
        return a / b;
    }
};

class CALCTEST : public ::testing::Test
{
protected:
    std::shared_ptr<CALC> calc;

public:
    CALCTEST()
    {
        calc = std::make_shared<CALC>();
    }
    ~CALCTEST() = default;
};

TEST_F(CALCTEST, ADD)
{
    EXPECT_EQ(3, calc->Add(1, 2));
}

TEST_F(CALCTEST, DIVIDE)
{
    EXPECT_EQ(3, calc->Divide(6, 1));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
