#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"
using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::UnitTest;

/**
 * @brief 检查内存泄漏
*/

namespace
{
class Water
{
public:
    void *operator new(size_t allocation_size)
    {
        allocated_++;
        return malloc(allocation_size);
    }

    void operator delete(void *block, size_t)
    {
        allocated_--;
        free(block);
    }

    static int allocated()
    {
        return allocated_;
    }

private:
    static int allocated_;
};

int Water::allocated_ = 0; //静态成员与类相关联，但是与类的实例无关

class LeakChecker : public EmptyTestEventListener
{
private:
    void OnTestStart(const TestInfo & /* test_info */) override
    {
        initially_allocated_ = Water::allocated(); //测试开始获取计数
    }

    void OnTestEnd(const TestInfo & /* test_info */) override
    {
        int difference = Water::allocated() - initially_allocated_;

        //若内存不泄露，当前读取的值小于等于初始值
        EXPECT_LE(difference, 0) << "Leaked " << difference << " unit(s) of Water!";
    }

    int initially_allocated_;
};

TEST(ListenersTest, DoesNotLeak)
{
    Water *water = new Water;
    delete water;
}

//只有new， 没有delete， 将会导致内存泄漏
TEST(ListenersTest, LeaksWater)
{
    Water *water = new Water;
    EXPECT_TRUE(water != nullptr);
}
} // namespace

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);

    bool check_for_leaks = false;
    if (argc > 1 && strcmp(argv[1], "--check_for_leaks") == 0)
        check_for_leaks = true;
    else
        printf("%s\n", "Run this program with --check_for_leaks to enable "
                       "custom leak checking in the tests.");

    if (check_for_leaks)
    {
        TestEventListeners &listeners = UnitTest::GetInstance()->listeners();

        listeners.Append(new LeakChecker);
    }
    return RUN_ALL_TESTS();
}
