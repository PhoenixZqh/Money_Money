#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QIcon>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);  //传入是金币还是银币

    //金币属性
    int posX;
    int posY;
    bool flag;
    int min, max;

    //改变标志的方法
    void changeFlag();
    QTimer* timer1;
    QTimer* timer2; //反面翻正面的定时器

    //执行动画标志
    bool isAnimation = false;

    //重写按下和释放操作
    void mousePressEvent(QMouseEvent* e);

    bool isWin = false;




signals:

};

#endif // MYCOIN_H
