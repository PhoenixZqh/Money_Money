#include "mywidget.h"

#include <QApplication>  //包含 一个应用程序类

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MyWidget w;  //窗口对象， 必须调用show方法显示
    w.show();
    return a.exec();


}
