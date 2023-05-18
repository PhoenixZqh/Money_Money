A&&B 的短路操作
	1. 如果A为true，则直接返回B的bool值
	2. 如果A为false，则直接返回false


```c++
class Solution {
public:
    int sumNums(int n) {
        n && (n += sumNums(n-1));
        return n;
    }
};
```