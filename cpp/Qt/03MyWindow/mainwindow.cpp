#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{

    resize(600, 400);
    setWindowTitle("WindowStudy");

    //创建菜单栏,最多只能有一个
    QMenuBar* bar = menuBar();

    //将菜单栏添加到窗口中
    setMenuBar(bar);

    //创建菜单
    QMenu* fileMenu =  bar->addMenu("文件");  //用fiemenu来接收文件这个菜单， 方便后续执行动作
    QMenu* editMenu = bar->addMenu("编辑");

    //创建菜单项目
    QAction* newaction = fileMenu->addAction("新建");

    fileMenu->addSeparator();      //添加分隔符号
    QAction* openaction = fileMenu->addAction("打开");


    //工具栏，可以有多个
    QToolBar* toolbar = new QToolBar(this);  // 加入到对象树中
    addToolBar(Qt::LeftToolBarArea, toolbar);

    //设置停靠位置
    toolbar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //设置浮动
    toolbar->setFloatable(false);

    //设置移动(总开关)
    toolbar->setMovable(true);

    //在工具栏中设置内容
    toolbar->addAction(newaction);
    toolbar->addSeparator();
    toolbar->addAction("打开");

    //在工具栏中添加控件
    QPushButton * btn = new QPushButton("按钮",this);
    toolbar->addWidget(btn);


    //状态栏，最多一个
    QStatusBar * statBar = statusBar();

    //将状态栏设置到窗口中
    setStatusBar(statBar);

    //放标签控件
    QLabel * label1 = new QLabel("当前状态", this);

    statBar->addWidget(label1);

    //设置中心部件
    QTextEdit * txtedit = new QTextEdit(this);
    setCentralWidget(txtedit);

}

MainWindow::~MainWindow()
{
}

