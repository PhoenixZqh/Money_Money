#ifndef MYEVENT_H
#define MYEVENT_H

#include <QWidget>

namespace Ui {
class MyEvent;
}

class MyEvent : public QWidget
{
    Q_OBJECT

public:
    explicit MyEvent(QWidget *parent = nullptr);
    ~MyEvent();

private:
    Ui::MyEvent *ui;
};

#endif // MYEVENT_H
