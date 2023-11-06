#include <iostream>
#include <cstring>

using namespace std;

// int main()
// {
//     char name[20];    //字符的长度不能超过19,因为‘\0’占了一个位置
//     char food[20];

//     cout << "Enter your name";
//     cin.getline(name,20);
//     cout << "Enter your favorite food";
//     cin.getline(food,20);

//     cout << "I will prepare " << food << ", for you ," << name << endl; 
 
//     return 0;
// }

//---------------------------------------------------------- get() ------------------------------------------------------------//
int main()
{
    char name[20];    //字符的长度不能超过19,因为‘\0’占了一个位置
    char food[20];

    cout << "Enter your name: ";
    cin.get(name,20).get();
    cout << "Enter your favorite food: ";
    cin.get(food,20);

    cout << "I will prepare " << food << ", for you ," << name << endl; 
 
    return 0;
}

//----------------------------------------------------------- sizeof & strlen -----------------------------------------------------------------//

// int main()
// {
//     char str[] = "hello world";

//     cout << "strlen compute: " << strlen(str) << endl;
//     cout << "sizeof compute: " << sizeof(str) << endl;
//     return 0;
// }