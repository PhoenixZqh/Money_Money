#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>


Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->teac = new Teacher(this);   //写this是为了加入到对象树中
    this->stu = new Student(this);



    //创建button
    QPushButton* btn1 = new QPushButton;
    this->resize(400, 400);
    btn1->setParent(this);
    btn1->setText("下课");
    btn1->move(100, 100);


//    connect(teac, &Teacher::Hungry, stu, &Student::Treat);

    //当信号和槽发生重载后，连接带参数的那一个，利用函数指针指向函数的地址
    void(Teacher::*teacPtr)(QString) = &Teacher::Hungry;
    void(Student::*stuPtr)(QString) = &Student::Treat;

    connect(teac, teacPtr, stu, stuPtr);

//    connect(btn1, &QPushButton::clicked, stu, &Student::Treat);
    /*connect(btn1, &QPushButton::clicked, this, &Widget::ClassisOver);*/ //点击按钮触发下课， 然后释放航哥饿了的信号，最后触发请航哥吃饭的槽函数

    //断开信号,参数与connect一致
//    disconnect(teac, teacPtr, stu, stuPtr);

    /*
     * 信号可以连接信号
     * 一个信号可以连接多个槽函数
     * 多个信号可以连接一个槽函数
     * 一个信号可以连接多个槽函数
     * 信号的类型需要与槽函数需要的一一对应
    */


    connect(btn1, &QPushButton::clicked, this, &Widget::ClassisOver);

    //调用下课信号
    ClassisOver();


    {
        QPushButton* btn2 = new QPushButton;
        btn2->setText("yes!");
        btn2->setParent(this);

        //利用lamda表达式实现点击按钮关闭窗口功能
        connect(btn2, &QPushButton::clicked, this, [this]()
        {
//            this->close();
            this->ClassisOver();
        });

    }

}


Widget::~Widget()
{
    delete ui;
}


void Widget::ClassisOver()
{
    emit teac->Hungry("beef");   //自定义信号触发关键字 emit
//    close();
}


