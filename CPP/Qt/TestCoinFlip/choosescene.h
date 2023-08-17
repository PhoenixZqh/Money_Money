#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <mypushbutton.h>
#include <QLabel>
#include <QDebug>
#include <playscene.h>

class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent * event);

signals:
    //写一个自定义信号，告诉主场景返回
    void chooseSceneBack();

private:
    PlayScene* play1 = nullptr;

};

#endif // CHOOSESCENE_H
