#include "mywidget.h"
#include <QPushButton>   //按钮头文件
#include <mypushbutton.h>

MyWidget::MyWidget(QWidget* parent)
    : QWidget(parent)
{
    QPushButton* myBtn = new QPushButton;
//    myBtn->show();    //show是以顶层方式弹出窗口控件
    myBtn->setParent(this);   //让myBtn对象依赖在myWidget窗口中
    myBtn->setText("第一个按钮");

    QPushButton* myBtn2 = new QPushButton("第二个按钮", this);   //按照控件的大小创建窗口

    myBtn2->move(500, 500);  //移动控件位置

    resize(1000, 1000);  //设置窗口大小

    setWindowTitle("第一个窗口");


    //测试对象树的自动释放
    MyPushButton* myBtn3 = new MyPushButton;
    myBtn3->setText("我自己的按钮");
    myBtn3->move(200, 200);
    myBtn3->setParent(this);


    //点击下我的按钮，关闭窗口
    //connect(信号的发送者，发送的信号(函数的地址)，信号的接收者，槽函数)
//    connect(myBtn3, &MyPushButton::clicked, this, &MyWidget::close);   //方式一
//    connect(myBtn3, &QPushButton::clicked, this, &QWidget::close); //方式二

}

MyWidget::~MyWidget()
{

}


