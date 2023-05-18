#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ratio_(1.0)
    , pos_(0)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [ = ]()
    {
        ratio_ -= 0.1;
//        pos_ += 20;

        qDebug() << "ratio_:" << ratio_;

        update();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* pe)
{
    //实例化画家对象
    QPainter painter(this);  //this, 指定的是绘图的设备（在当前窗口）

    //设置画笔
    QPen pen(QColor(255, 0, 0));

    painter.setPen(pen); //让画家使用这个笔

    painter.drawLine(QPoint(0, 0), QPoint(100, 100));

//    painter.drawEllipse(QRect(100,100,100,100));     //画椭圆，圆

//    painter.drawRect(QRect(QPoint(100, 100), QPoint(500, 500))); //画矩形

    painter.drawText(QRect(200, 200, 1000, 50), "好好学习，天天向上"); //画文字


    //***绘图高级设置

    painter.drawEllipse(QPoint(200, 50), 50, 50);
    painter.setRenderHint(QPainter::Antialiasing);  //设置抗锯齿能力， 但是效率会比较低
    painter.drawEllipse(QPoint(300, 50), 50, 50);

    painter.drawRect(QRect(QPoint(100, 100), QPoint(500, 500)));
    painter.translate(100, 100); //让画家移动
    painter.drawRect(QRect(QPoint(100, 100), QPoint(500, 500)));

    //***利用画家画图片
    QPixmap pix;
    pix.load(":/Pictures/3.jpeg");
    pix.scaled(pix.width() * ratio_, pix.height() * ratio_);
    painter.drawPixmap(pos_, pos_, pix);


}
