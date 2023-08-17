#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix ;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug() << str;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号
    min = 1, max = 8;
    connect(timer1, &QTimer::timeout, [ = ]()
    {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //如果翻转完了，重置mix
        if(this->min > this->max)
        {
            this->min = 1;
//            isAnimation = true;
            timer1->stop();
        }
    });

    connect(timer2, &QTimer::timeout, [ = ]()
    {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //如果翻转完了，重置mix
        if(this->max < this->min)
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });

}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin) return;

    else
    {
        QPushButton::mousePressEvent(e); // 将消息传递下去
    }
}

void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        this->flag = false;

    }
    else
    {
        timer2->start(30);
        this->flag = true;
    }
}
