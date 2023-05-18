#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionnew->setIcon(QIcon("/home/zqh/Pictures/3.jpeg")); // 为菜单添加图标

    //使用Qt添加资源 “:+前缀名+文件名”
    ui->actionopen->setIcon(QIcon(":/Pictures/1.jpeg"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

