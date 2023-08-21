#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

/*
 * @Author: Phoenix_Z
 * @Date: 2023-08-21 15:10:04
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2023-08-21 15:10:04
 * @Description: 删除原有文件夹下的文件，并将新的文件移动到原有文件夹下
 */

int main()
{
    std::string oldFilePath = "/home/zqh/phoenixZ/Money_Money/CPP/c++/src/文件操作/FolderA/a.txt"; // 老文件路径
    std::string newFilePath = "/home/zqh/phoenixZ/Money_Money/CPP/c++/src/文件操作/FolderB/DOC 文档.doc"; // 新文件路径

    // 获取旧文件的文件夹路径
    size_t lastSlash = oldFilePath.find_last_of('/');
    std::string oldFileparent = oldFilePath.substr(0, lastSlash);

    std::string old_file_dir = oldFileparent + "/" + "a.doc";

    // 删除老文件
    if (std::remove(oldFilePath.c_str()) != 0) {
        std::cerr << "Error deleting the old file." << std::endl;
        return 1;
    }

    if (std::rename(newFilePath.c_str(), old_file_dir.c_str()) == 0) {
        std::cout << "文件移动成功！" << std::endl;
    } else {
        std::cerr << "文件移动失败" << std::endl;
    }

    return 0;
}
