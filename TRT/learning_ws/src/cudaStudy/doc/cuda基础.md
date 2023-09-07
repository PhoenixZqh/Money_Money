1. 一个核函数只能有一个grid，一个grid可以有很多个块，每个块可以有很多的线程![](./img/4.png)
<font color = "green">  
- grid有多大，用gridDim 表示他有多少个block ,具体分为gridDim.x,gridDim.y,gridDim
- block有多大，用blockDim表示他有多少个thread，具体分为blockdDim.x,blockdDim.y,blockdDim.z
- threadIdx.x, threadIdx.y, threadIdx.z表示线程在block中的相对位置
- blockIdx.x ,blockIdx.y,blockIdx.z 表示block 在grid中的相对位置
</font>

1. 一个线程块的线程可以完成：同步 && 内存共享； 不同块内线程不能相互影响，因为是物理隔离的

2. 根据两个内置结构体确定线程标号：
   
   - blockIdx（线程块在线程网格内的位置索引）
   - threadIdx（线程在线程块内的位置索引）
   
3. kernel核函数编写限制
   - 只能访问设备内存
   - 必须有void返回类型
   - 不支持可变数量的参数
   - 不支持静态变量
   - 显示异步行为

4. 组织并行线程
   
   ![](./img/cuda_thread.png)

   
   这里(ix,iy)就是整个线程模型中任意一个线程的索引，或者叫做全局地址，局部地址当然就是(threadIdx.x,threadIdx.y)了，当然这个局部地址目前还没有什么用处，他只能索引线程块内的线程，不同线程块中有相同的局部索引值，比如同一个小区，A栋有16楼，B栋也有16楼，A栋和B栋就是blockIdx，而16就是threadIdx啦

5. 查询设备信息


   | 函数                      | 作用                              | 用法 |
   | ------------------------- | --------------------------------- | ---- |
   | cudaGetDeviceCount()      | 获取CUDA设备数目                  |      |
   | cudaGetDeviceProperties() | 获取 CUDA 设备的属性              |      |
   | cudaSetDevice()           | 设置用于GPU执行的设备             |      |
   | cudaGetDeviceProperties() | 返回有关计算设备的信息            |      |
   | cudaDriverGetVersion()    | 返回驱动程序支持的最新版本的 CUDA |      |
   | cudaRuntimeGetVersion()   | 返回 CUDA 运行时版本              |      |
   |                           |                                   |
   |                           |                                   |      |
   |                           |                                   |      |
   |                           |                                   |      |
   