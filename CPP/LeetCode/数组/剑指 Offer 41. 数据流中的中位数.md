如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5


```c++
class MedianFinder {
public:
    /** initialize your data structure here. */
    
    priority_queue<int> dading;
    priority_queue<int, vector<int>, greater<int> > xiaoding;
    MedianFinder() {
    }
    
    void addNum(int num) {
        
        dading.push(num);
        xiaoding.push(dading.top());
        dading.pop();
        if(dading.size() < xiaoding.size())
        {
            dading.push(xiaoding.top());
            xiaoding.pop();
        }
    }
    
    double findMedian() {
        return dading.size() != xiaoding.size()? double(dading.top()) : (dading.top() + xiaoding.top()) * 0.5;
    }
};
```