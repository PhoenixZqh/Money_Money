#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(420, 760);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("赚钱啦赚钱啦");

    //点击退出->关闭窗口
    connect(ui->actionexit, &QAction::triggered, [ = ]()
    {
        this->close();
    });


    //准备开始按钮音乐音效
//    QSound* startSound = new QSound(":/res/TapButtonSound.wav", this);  //this代表让谁播放


    //开始按钮
    MyPushButton* startbtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width() * 0.5 - startbtn->width() * 0.5, this->height() * 0.8);

    cho = new ChooseScene; // 实例化选择关卡的场景

    //监听选择关卡的按钮信号
    connect(cho, &ChooseScene::chooseSceneBack, this, [ = ]()
    {
                this->setGeometry(cho->geometry()) ;
        QTimer::singleShot(500, [ = ]()
        {
            //进入到选择关卡场景中,并将自己隐藏
            cho->hide();
            this->show();

        });

    });

    connect(startbtn, &MyPushButton::clicked, [ = ]()
    {
        //播放开始音效资源
//        startSound->play();

        //点击开始按钮，触发弹起的特效
        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入
        QTimer::singleShot(500, [ = ]()
        {
            //设置cho当前场景的位置
            cho->setGeometry(this->geometry());

            //进入到选择关卡场景中,并将自己隐藏
            this->hide();
            cho->show();

        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::paintEvent(QPaintEvent* event)
{
    //创建画家
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, 420, 760, pix);

    pix.load(":/res/Title.png");
    pix.scaled(pix.width() * 0.8, pix.height() * 0.8);
    painter.drawPixmap(0, 0, pix);

}
