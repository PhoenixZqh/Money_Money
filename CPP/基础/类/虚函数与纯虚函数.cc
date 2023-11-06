#include <iostream>

using namespace std;

//创建基类
class Parent
{
private:
   
public:
    float milk_pieces;
    virtual void buy_milk()
    {
        cout << "im father, i have " << milk_pieces << "RMB" << endl;
    }
    
    Parent(float mp):milk_pieces(mp){}
    Parent(){}
    virtual ~Parent(){}
};

//创建子类
class Child1 : public Parent
{
private:
    int m_p;
public:
    virtual void buy_milk()
    {   
        cout << " im child 1 , i need " << m_p << "RMB \t to buy milk" << endl;
    }

    Child1(int mp): m_p(mp){ }
    virtual ~Child1(){}
    
};







int main()
{
    Parent *p = new Parent(199.2);
    p->buy_milk();
    
    Parent *p1 = new Child1(200);
    p1->buy_milk();

    return 0;
}