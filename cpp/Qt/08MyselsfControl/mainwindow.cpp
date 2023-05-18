#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击获取控件当前的值
    connect(ui->pushButton, &QPushButton::clicked, [ = ]()
    {
        qDebug() << ui->widget->GetNUm();
    });

    //点击设置控件当前的值
    connect(ui->pushButton_2, &QPushButton::clicked, [ = ]()
    {
        ui->widget->SetNum(50);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

