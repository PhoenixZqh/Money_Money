#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    //自定义信号 写到signals下
    //返回值是void，只需要声明，不需要实现
    //可以有参数，可以重载
    void Hungry();

    void Hungry(QString foodname);

};

#endif // TEACHER_H
