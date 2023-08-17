输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
 
```c++
class Solution {
public:
    int findPartion(vector<int> &arr , int left, int right)
    {
        int tmp = arr[left];
        while(left < right)
        {
            while(left < right && arr[right] >= tmp)
            {
                right--;
            }
            if(left < right) arr[left] = arr[right];
            while(left < right && arr[left] <= tmp)
            {
                left++;
            }
            if(left < right) arr[right] = arr[left];
        }
        arr[left] = tmp;
        return left;
}
void quickSort(vector<int> &arr, int left , int right)
{   
    if(left < right)
    {
        int keypos = findPartion(arr, left, right);
        quickSort(arr,left,keypos-1);
        quickSort(arr,keypos+1,right);
    }
    
}
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        quickSort(arr,0,arr.size()-1);
        vector<int> res(arr.begin(),arr.begin()+k);
        return res;
    }
};
```
