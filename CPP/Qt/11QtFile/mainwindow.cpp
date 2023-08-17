#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {

        QString path = QFileDialog::getOpenFileName(this, "打开文件", "/home/zqh/Documents");

        ui->lineEdit->setText(path); //将路径保存到lineedit中

        //编码格式类
        QTextCodec* codec = QTextCodec::codecForName("gbk");    //先判断文件格式

        //读取内容到textedit中
        QFile file(path);   //参数就是读取文件路径
        file.open(QIODevice::ReadWrite);

        QByteArray array = file.readAll();
//       ui->textEdit->setText(array);    //将读取数据放入textEdit中
        ui->textEdit->setText(codec->toUnicode(array)) ;

        file.close();

        //***文件信息
        QFileInfo info (path);
        qDebug() << "文件大小： " << info.size()
                 << "文件名称: " << info.fileName()
                 << "文件后缀：" << info.suffix()
                << "创建日期: " << info.created();




    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

