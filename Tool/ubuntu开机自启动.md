1. 终端打开gnome
   ```xml
    gnome-session-properties
   ```

2. 创建脚本文件，并赋权限
   ```xml
   sudo chmod +x *.sh
   ```

3. 在gnome中新建自启动项
   ```xml
   gnome-terminal -- bash -c "sh /home/*/*.sh; exec bash"
   ```