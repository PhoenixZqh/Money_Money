#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject* parent = nullptr);
    void Treat();
    void Treat(QString foodname);

signals:

public slots:
    /*
     * 早期必须写在 public slots中， 高级版本可以写到public 或者 全局下
     * 返回值是void，需要声明，也需要实现
     * 可以有参数，可以发生重载
    */

//    void Treat();


};

#endif // STUDENT_H
