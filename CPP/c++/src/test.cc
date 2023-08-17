#include <cmath>
#include <iostream>
#include <queue>
#include <string>

// struct Person {
//     std::string name;
//     int age;
//     Person(const std::string& n, int a)
//         : name(n)
//         , age(a)
//     {
//     }
// };

// struct PersonCompare {
//     bool operator()(const Person& p1, const Person& p2) const
//     {
//         return p1.age > p2.age; // 为true的时候表示p1的优先级高，
//     }
// };

// int main()
// {
//     std::priority_queue<Person, std::vector<Person>, PersonCompare> pq;

//     pq.push(Person("Alice", 25));
//     pq.push(Person("Bob", 30));
//     pq.push(Person("Charlie", 20));

//     while (!pq.empty()) {
//         std::cout << pq.top().name << " " << pq.top().age << std::endl;
//         pq.pop();
//     }

//     return 0;
// }
using namespace std;

#define PI 3.1415926

void ComputeAngle(double x0, double y0, double x1, double y1)
{
    double delta_x = x1 - x0;
    double delta_y = y1 - y0;

    double angle = atan2(delta_y, delta_x);

    cout << "angle: " << angle * 180 / PI << endl;

    if (angle < 0) {
        angle += 2 * PI;
    }

    double res_angle = angle * 180 / PI;

    cout << "计算得到夹角为: " << res_angle << endl;
}

int main()
{
    double x = 0, y = 0;
    double x1 = 0.0, y1 = -1.0;

    ComputeAngle(x, y, x1, y1);

    return 0;
}
