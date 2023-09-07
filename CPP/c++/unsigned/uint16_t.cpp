#include <cstdint>
#include <iostream>

/**
 * @brief  uint16_t 与 int 的区别
 *         1. uint16_t 是无符号类型，表示范围内的整数值都是正数，取值范围在 0～ 2^16-1，通常占据2字节
 *         2. int 是带符号整形类型，取值范围是-2,147,483,648 ～ 2,147,483,647， 通常占据4字节
 */

int main()
{
    uint16_t number;

    while (true) {
        std::cout << "请输入一个 uint16_t 值 (0 到 65535): ";
        if (!(std::cin >> number)) {
            continue; // 继续循环等待有效输入
        }

        // 在这里处理有效的整数输入
        std::cout << "您输入的 uint16_t 值是: " << number << std::endl;
    }

    return 0;
}
