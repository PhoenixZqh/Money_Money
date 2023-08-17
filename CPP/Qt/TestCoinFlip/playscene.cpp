#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了人第%1关").arg(levelNum);  //占位
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    this->setFixedSize(420, 760);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");

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
        emit this->chooseSceneBack();
    });

    //显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setPointSize(20);
    QString str1 = QString("Level:%1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {

            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load("/home/zqh/11.png");
    qDebug() << "***********8" << tmpPix.width();
    winLabel->setGeometry(0, 0, tmpPix.width()/500, tmpPix.height()/500);
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());



    //显示金币背景图案

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //绘制背景图片
            QLabel* label2 = new QLabel;
            label2 -> setGeometry(0, 0, 100, 100);
            label2 ->setPixmap(QPixmap(":/res/BoardNode.png"));
            label2->setParent(this);
            label2->move(88 + i * 60, 250 + j * 60);

            QString str;
            //创建金币
            if(this->gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(90 + i * 60, 280 + j * 60);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将金币状态加入金币的二维数组中，方便后续维护
            btnCoin[i][j] = coin;

            //点击金币进行反转
            connect(coin, &MyCoin::clicked, [ = ]()
            {
                //点击按钮将所有金币禁用
                for(int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {

                            this->isWin = true;

                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                QTimer::singleShot(300, this, [ = ]()
                {
                    //翻转周围金币, 并且添加演示反转
                    if(coin->posX + 1 <= 3) //当前金币右侧金币翻转的条件
                    {
                        btnCoin[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin->posX - 1 >= 0) //左侧金币翻转条件
                    {
                        btnCoin[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin->posY + 1 <= 3)
                    {
                        btnCoin[coin->posX ][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }

                    if(coin->posY - 1 >= 0)
                    {
                        btnCoin[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX ][coin->posY - 1] = this->gameArray[coin->posX ][coin->posY - 1] == 0 ? 1 : 0;
                    }

//                    this->isWin = true;
                    //翻完周围金币后，将所有金币禁用

                    for(int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if(btnCoin[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if(this->isWin == true)
                    {
                        qDebug() << "游戏胜利";

                        for(int i = 0; i < 4; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                btnCoin[i][j]->isWin = true;  //将所有按钮改为ture，所有的按钮都能按了
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation* ani1 = new QPropertyAnimation(winLabel, "geometry");

                        ani1->setDuration(1500); //设置时间间隔

                        //设置开始、结束的位置、缓和的曲线
                        ani1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        ani1->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
                        ani1->setEasingCurve(QEasingCurve::OutBounce);

                        //执行动画
                        ani1->start();

                    }
                });

            });

        }
    }



}

void PlayScene::paintEvent(QPaintEvent* e)
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
