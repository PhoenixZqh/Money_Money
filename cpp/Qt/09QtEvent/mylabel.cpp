#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent)
{
    //设置鼠标追踪, 默认状态为false
    setMouseTracking(true); //直接捕获到鼠标移动
}

void MyLabel::enterEvent(QEvent* event)
{
    qDebug() << "鼠标进入";

}

void MyLabel::leaveEvent(QEvent* event)
{
    qDebug() << "鼠标离开了 ";
}

void MyLabel::mouseMoveEvent(QMouseEvent* ev)
{
    qDebug() << "鼠标移动了 ";
}

void MyLabel::mousePressEvent(QMouseEvent* ev)
{
    //设置左键打印
//    if(ev->button() == Qt::LeftButton)
//    {
    QString str = QString("鼠标按下了 ， x=%1  y=%2 ").arg(ev->x()).arg(ev->y());    //qt语法
    qDebug() << str;


}


void MyLabel::mouseReleaseEvent(QMouseEvent* ev)
{
    qDebug() << "鼠标释放了 ";

}

bool MyLabel::event(QEvent* e)
{
    if(e->type() == QEvent::MouseButtonPress)     //使用事件分发器拦截事件
    {
        QMouseEvent* ev = static_cast<QMouseEvent*>(e);    //c++静态类型转换
        QString str = QString("Event鼠标按下了 ， x=%1  y=%2 ").arg(ev->x()).arg(ev->y());    //qt语法
        qDebug() << str;

        return  true;
    }

    return QLabel::event(e);      //其他事件交给父类处理

}


