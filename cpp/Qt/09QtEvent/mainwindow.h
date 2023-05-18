#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timerEvent(QTimerEvent * event);  //重写定时器

private:
    Ui::MainWindow *ui;
    int id1, id2, id3;
    bool flag;
    QPushButton* btn;
    QTimer* timer;

    void setPushButton(QTimer * timer_);
};
#endif // MAINWINDOW_H
