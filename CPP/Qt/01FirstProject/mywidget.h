#ifndef MYWIDGET_H
#define MYWIDGET_H
#pragma execution_character_set("utf-8")


#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
