#include <yaml_learn.h>
#include <yaml-cpp/yaml.h>
#include <memory>

int main()
{
    string yaml_path = "/home/zqh/文档/Money_Money/ROS/learn_yaml/config/array.yaml";
    YAML::Node config = YAML::LoadFile(yaml_path);
    auto stu = make_shared<YamlLearn>(config["Student"]); //用make_shared的方式初始化shared_ptr指针
    stu->print();
    cout << "指针引用: " << stu.use_count() << endl;
}
