#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QAction>
#include <QMenuBar>
#include <QEvent>
#include <QPainter>
#include <QPixmap>
#include <mypushbutton.h>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QTimer>
#include <QPropertyAnimation>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;  //记录所选的关卡

    void paintEvent(QPaintEvent* e);
    int gameArray[4][4]; // 二位数组维护每个关卡的具体数据
    MyCoin * btnCoin[4][4];  //记录周围金币的状态

    //是否胜利的标志
    bool isWin;
signals:
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
