#include "mainwindow.h"
#include "./ui_mainwindow.h"

/*
 *事件分发
*/



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , flag(false)
{
    ui->setupUi(this);
//    id1 =startTimer(100);  //参数1, 间隔，单位毫秒;返回值为计时器id

//    id2 = startTimer(1000);


    //***定时器的第二种方式,推荐
//    QTimer * timer= new QTimer(this);

    //启动定时器
    static int num3 = 0;
    timer = new QTimer(this);
    timer->start(500);
    connect(timer, &QTimer::timeout, [ = ]()
    {
        ui->label_4->setText(QString::number(num3++));

    });

    //创建一个按钮，按一下暂停计时
    btn = new QPushButton(this);
    btn->setText("暂停计时");
    btn->move(20, 20);

    connect(btn, &QPushButton::clicked, [ = ]()
    {

        this->setPushButton(timer);
    });




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    static int num = 1;
    static int num2 = 1;


    if(event->timerId() == id1)
    {
        ui->label_2->setText(QString::number(num++));
    }

    if(event->timerId() == id2)
    {
        ui->label_3->setText(QString::number(num2++));

    }


}

void MainWindow::setPushButton(QTimer* timer_)
{

    if(flag)
    {
        timer_->start(100);
        btn->setText("START");
        flag = false;

    }

    else
    {
        timer_->stop();
        btn->setText("STOP");
        flag = true;
    }

}

