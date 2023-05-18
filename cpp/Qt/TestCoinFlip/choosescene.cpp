#include "choosescene.h"

ChooseScene::ChooseScene(QWidget* parent) : QMainWindow(parent)
{


    //配置选择关卡的场景

    this->setFixedSize(420, 760);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar* bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");

    //创建推出菜单项
    QAction* quitaction = startMenu->addAction("退出");

    connect(quitaction, &QAction::triggered, [ = ]
    {
        this->close();
    });

    MyPushButton* backbtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width(), this->height() - backbtn->height());

    connect(backbtn, &MyPushButton::clicked, [ = ]()
    {
//        qDebug() << "点击了返回按钮";
        //返回主场景，主场景监听ChooseLevelScene的返回按钮
        emit this->chooseSceneBack();   //自定义信号不需要具体实现
    });

    //创建选择关卡按钮
    for(int row = 0; row < 20; row++)
    {
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(75 + row % 4 * 80, 150 + row / 4 * 80);    //一个for循环实现二维矩阵

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [ = ]()
        {
            QString str = QString("您选择的是第%1关").arg(row + 1);  //占位
            qDebug() << str;

            this->hide(); //将选关场景隐藏掉
            play1 = new PlayScene(row + 1);
            play1->show();

            connect(play1, &PlayScene::chooseSceneBack, [ = ]()
            {
                this->show();
                delete play1;
                play1 = nullptr;
            });

        });


        QLabel* label1 = new QLabel;
        label1->setParent(this);
        label1->setFixedSize(menuBtn->width(), menuBtn->height());
        label1->setText(QString::number(row + 1));
        label1->move(75 + row % 4 * 80, 150 + row / 4 * 80);
        label1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);   //设置水平居中和垂直居中

        //设置让鼠标进行穿透
        label1->setAttribute(Qt::WA_TransparentForMouseEvents);    //51号属性

    }

}

void ChooseScene::paintEvent(QPaintEvent* event)
{

    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
