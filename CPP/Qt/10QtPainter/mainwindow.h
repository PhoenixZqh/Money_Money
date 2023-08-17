#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>    //画家类
#include <QPushButton>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //绘图事件
    void paintEvent(QPaintEvent * pe);

private:
    Ui::MainWindow *ui;

    float ratio_;
    int pos_;
};
#endif // MAINWINDOW_H
