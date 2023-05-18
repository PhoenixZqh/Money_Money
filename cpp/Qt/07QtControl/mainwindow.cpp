#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //设置单选按钮，男默认选中
    ui->rBtnMan->setChecked(true);

    connect(ui->rBtnWomen, &QToolButton::clicked, []()
    {
        qDebug() << "选中女性了";
    });

    connect(ui->checkBox, &QCheckBox::clicked, []()
    {
        qDebug() << "奖励厨子一辆劳斯莱斯";
    });

    connect(ui->checkBox_2, &QCheckBox::stateChanged, [ = ](int state)  //多选按钮，2是选中，0是未选中
    {
        qDebug() << state;
    });

    //***listwidget学习
    QListWidgetItem* item1 = new QListWidgetItem("胸有惊雷而面如平湖者，可拜上将军");   //第一种方式
    ui->listWidget->addItem(item1);

    QStringList list;        //第二种方式
    list << "不错" << "好" ;
    ui->listWidget->addItems(list);


    //***treewidget学习
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    //加载顶层节点
    QTreeWidgetItem* item2 = new QTreeWidgetItem(QStringList() << "力量");
    ui->treeWidget->addTopLevelItem(item2);

    //追加子节点
    QStringList hero ;
    hero << "刘邦" << "吃和票";
    QTreeWidgetItem* item21 = new QTreeWidgetItem(hero);

    item2->addChild(item21);


    //***tableWidget学习

//    QTableWidgetItem * item3 = new QTableWidgetItem("学习");
//    ui->tableWidget->setItem(3,3,item3);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "性别" << "年龄");
//    ui->tableWidget->setItem(0,0,new QTableWidgetItem("刘邦"));

    QStringList names;
    names << "刘邦" << "赵云" << "詹姆斯" << "奥巴马" << "卡带山";

    QStringList aaa;
    aaa << "男" << "男" << "男" << "男" << "女";

    for(int i = 0; i < 5; i++)
    {
        int col = 0;
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(names[i]));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(aaa[i]));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number( i + 19)));

    }

    ui->tableWidget->resize(350, 200);

    //***Qlabel学习

//    QPixmap pix;
//    pix.load("/home/zqh/Pictures/1.jpeg");
//    ui->label->setGeometry(0,0,pix.width(),pix.height());
//    ui->label->setPixmap(pix);


    //*** stacked widget学习
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->pushButton_9,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->pushButton_10,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->pushButton_11,&QPushButton::clicked,[](){
        qDebug() << "我实现了";
    });







}

MainWindow::~MainWindow()
{
    delete ui;
}

