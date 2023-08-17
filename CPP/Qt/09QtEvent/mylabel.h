#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QTimerEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget* parent = nullptr);

    void enterEvent(QEvent* event);   //鼠标进入事件
    void leaveEvent(QEvent* event);


    void mouseMoveEvent(QMouseEvent* ev);  //鼠标移动事件
    void mousePressEvent(QMouseEvent* ev); // 鼠标按下事件
    void mouseReleaseEvent(QMouseEvent* ev); //鼠标释放事件

    bool event(QEvent* e);       //通过event事件分发器 拦截 鼠标按下的事件

signals:

};

#endif // MYLABEL_H
