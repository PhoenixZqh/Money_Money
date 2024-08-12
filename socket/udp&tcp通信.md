# 通信流程

1. 创建套接字对象

   ```
   udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #udp通信

   tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #tcp通信

   ```
2. 绑定服务端主机ip以及端口
3. 发送/接受数据

   ```
   # 发送数据
   socketObj.sendto( data, targetAddr )

   # 接受数据
   socketObj.recvfrom( maxSize )
   ```
4. 关闭套接字

   ```
   u看到飞机socketObj.close()
   ```

# UDP与TCP的区别

| 通信方式 |                              |                                  |
| -------- | ---------------------------- | -------------------------------- |
| udp      | 无需建立连接，开销小         | 实时性较高，但可能丢包           |
| tcp      | 需要建立连接，维护状态开销大 | 传输更加可靠，不会丢包，不会损坏 |

# 什么是socket套接字

socket 套接字，可以在不同计算机/不同进程中通信， 套接字通常由一对ip与端口号作为唯一标识
