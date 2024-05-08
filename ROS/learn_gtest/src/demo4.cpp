#include <iostream>
#include <gtest/gtest.h>
#include <memory>

/**
 * @brief 基本类型检查
 * * 数值检查
 *   1. EQ：equal， 预期值与实际值相等
 *   2. NE：not equal， 预期值与实际值不相等
 *   3. LT：less than， 预期值小于实际值
 *   4. LE：less than or equal to , 预期值小于等于实际值
 *   5. GT：greater than， 预期值大于实际值
 *   6. GE：greater than or equal to， 预期值大于等于实际值
 * * 布尔型检查
 *   1. TURE：  运行结果为frue / 非0
 *   2. FALSE： 运行结果为false / 0
 * * 字符串检查
 *   1. STREQ : string equal 比较的两个字符串是相同的
     2. STRNE : string not equal 比较的两个字符串不相同
     3. STRCASEEQ : string equal ignore case 忽略大小写，比较的两个字符串相同
     4. STRCASENE : string not equal ignore case 忽略大小写，比较的两个字符串不同

*/

class CALC
{
public:
    char name[10];

    CALC() = default;
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
    EXPECT_EQ(3, calc->Add(1, 2)); //right
    EXPECT_NE(3, calc->Add(1, 2)); //error
    EXPECT_LT(3, calc->Add(1, 2)); //error
    EXPECT_LE(3, calc->Add(1, 2)); //right
    EXPECT_GT(3, calc->Add(1, 2)); //error
    EXPECT_GE(3, calc->Add(1, 2)); //right
}

TEST_F(CALCTEST, MINUS)
{
    EXPECT_TRUE(calc->Minus(3, 2));  //right
    EXPECT_FALSE(calc->Minus(3, 2)); //error
}

TEST_F(CALCTEST, CHAR)
{
    strcpy(calc->name, "googletest");
    EXPECT_STREQ("GOOGLETEST", calc->name);     //error
    EXPECT_STRCASEEQ("GOOGLETEST", calc->name); //right
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}