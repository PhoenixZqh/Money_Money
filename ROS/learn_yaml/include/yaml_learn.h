#ifndef YAML_LEARN_H
#define YAML_LEARN_H

/*
创建yaml文件
读取yaml文件
读取的方式可以一个一个读
也可以创建个类的智能指针去获取yaml的内容
假设这个yaml的内容是学生的信息，包括学生姓名、年龄、成绩
*/
#include <iostream>
#include <yaml-cpp/yaml.h>

using namespace std;

class YamlLearn
{
private:
    string m_name;
    int m_age;
    float m_score;
    std::vector<int> m_arr;

public:
    YamlLearn(const YAML::Node &config);
    ~YamlLearn();
    void print();
};
#endif