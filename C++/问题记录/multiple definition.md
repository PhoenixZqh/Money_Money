

1. 问题回顾
   
   a. 创建了tool.hpp, 并且在其中定义了函数和类，以及变量
   b. 在norm.cpp builder.cpp 中都包含了该.hpp
   c. 将norm.cpp builder.cpp 链接到可执行文件
   d. <font color=red>报错：multiple definition of ...</font>


2. 问题解决
   a. ~~一开始以为头文件反复包含的问题， 检查后没有解决~~
   b. ~~为每个定义的函数或者类加上static，解决了问题，但是引入了新的问题~~
   c. <font color = green> 头文件只做声明，源文件定义，问题解决 </font>

3. 原因分析
    
    ==不能将定义放在头文件中==
    原因是：如果将全局变量的定义放在头文件中，则该定义会转到包含该头文件的每个.cpp文件中

    [stackoverflow链接](https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error)
