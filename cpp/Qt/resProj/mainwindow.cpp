#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(320,588);   //设置固定大小
    setWindowIcon(QIcon(":/res/Coin0001.png")) ; //设置图标
    setWindowTitle("翻金币");

    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEent(QPaintEvent *)
{

    QPainter painter(this);   //在当前窗口上画画
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(10,10,320,588,pix);  //(起始位置，指定宽高，图片）
//    painter.drawRect(QRect(50,50,100,100));


    pix.load(":/res/Title.png");  //添加北京图标
    pix.scaled(pix.width() * 0.5, pix.height()*0.5);
    painter.drawPixmap(0,0,pix);
}

