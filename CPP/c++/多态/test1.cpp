
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Animal {
 private:
  string m_name;
  string m_bark;

 public:
  Animal();
  virtual ~Animal();

 protected:
  Animal();
};
