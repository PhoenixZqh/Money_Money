/*
 * @Author: Phoenix_Z
 * @Date: 2022-09-03 13:48:21
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-09-03 13:48:21
 * @Description: recursion 
*/

#include <iostream>
#include <memory>
 
using namespace std;
 
void testDigui(int n)
{
    cout << "before recursion, " << n << endl;   

    if(n<=0) return;        //递归终止条件                 
    testDigui(n-1);         //递归调用

    cout << "after recusion ," << n << endl;    //回溯返回阶段
}

int testJiecheng(int n)
{
    if(n == 0 ) return 1;
    int res = n * testJiecheng(n-1);
    cout << n << ":" <<  res << endl;;
    return res;
     
}

int main()
{   
    int res = testJiecheng(3);
    cout << res << endl;
    testDigui(5);
    return 0;
}