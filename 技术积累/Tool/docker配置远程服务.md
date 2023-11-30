1. 安装vim
   ```xml
   sudo apt install vim
   ```

2. 安装ssh
   ```xml
   sudo apt-get install openssh-server
   ```

3. SSH配置
   ```xml
   vi /etc/ssh/sshd_config   
   ```
    修改如下项：

    ```xml
    PermitRootLogin yes # 可以登录 root 用户
    PubkeyAuthentication yes # 可以使用 ssh 公钥许可 
    AuthorizedKeysFile	.ssh/authorized_keys # 公钥信息保存到文件 .ssh/authorized_keys 中 
    UsePAM no 
    ```

4. 设置ROOT账户密码
   ```xml
    passwd
    123
   ```

5. 启动ssh服务
    ```xml
    service ssh restart
    ```
6. 启动docker
   ```xml
   docker run -it -p 1022:22 phoenix1230/ubuntu20:v1 /bin/bash
   ```

7. 远程登录
   ```xml
   ssh root@127.0.0.1 -p 1022
   ```