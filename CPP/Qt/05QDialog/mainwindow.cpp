#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //点击信号槽，弹出一个对话框
    connect(ui->actionnew, &QAction::triggered, [this]()
    {
        // 对话框： 1.非模态对话框：可以对其他窗口进行操作；2.模态对话框：不能对其他窗口进行操作
        // 创建模态对话框,阻塞功能
//        QDialog dlg(this);
//        dlg.resize(400,200);
//        dlg.exec();


        //创建非模态对话框, 需要创建在堆上
        QDialog* dlg1 = new QDialog(this);   //对象树的释放是在关闭窗口后；有可能内存泄漏
        dlg1->setAttribute(Qt::WA_DeleteOnClose); //55号属性
        dlg1->resize(400, 200);
        dlg1->show();

        QMessageBox::critical(this, "critical", "错误");    //错误对话框
        QMessageBox::information(this, "info", "信息");     //信息对话框
        /*QMessageBox::question(this,"info", "提问", QMessageBox::Save|QMessageBox::Cancel, QMessageBox::Save);*/          //提问对话框，（父亲，标题名称，显示内容，关联按键的类型，默认关联回车按键）

        if(QMessageBox::Save == QMessageBox::question(this, "info", "提问", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save))
        {
            qDebug() << "选择的是保存" ;

        }

        else
        {
            qDebug() << "选择的是取消" ;
        }


    });

    connect(ui->actionopen, &QAction::triggered, [this]()
    {
        //其他颜色对话框
        QColorDialog::getColor(QColor(200, 0, 0, 255));

        //文件对话框 (父亲，标题， 默认打开的路径，过滤的文件的格式)
        QFileDialog::getOpenFileName(this, "打开文件", "/home/zqh/QT5");

        //字体对话框
        bool flag = true;
//        QFontDialog::getFont(&flag, QFont(" "，36));
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

