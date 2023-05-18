#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::Treat()
{
    qDebug() << "请航哥吃饭";
}

void Student::Treat(QString foodname)
{

    qDebug() << "请航哥吃：" << foodname.toUtf8().data();  //先转换成QByteArray ， 再转到char*
}
