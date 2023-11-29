#include <yaml_learn.h>

YamlLearn::YamlLearn(const YAML::Node &config)
{
    m_name = config["name"].as<string>();
    m_age = config["age"].as<int>();
    m_score = config["score"].as<float>();
    m_arr = config["arr"].as<std::vector<int>>();
}
YamlLearn::~YamlLearn()
{}

void YamlLearn::print()
{
    cout << m_name << ","
         << m_age << ", "
         << m_score << ", "
         << endl;

    for (auto i : m_arr)
    {
        cout << "arr: " << i << "\t" << endl;
    }
}
