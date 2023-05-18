#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QAction>
#include <mypushbutton.h>
#include <choosescene.h>
#include <QTimer>
#include <QObject>
#include <QtMultimedia/QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ChooseScene * cho = nullptr;


    void paintEvent(QPaintEvent * event);
};
#endif // MAINWINDOW_H
