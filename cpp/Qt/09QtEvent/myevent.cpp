#include "myevent.h"
#include "ui_myevent.h"

MyEvent::MyEvent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyEvent)
{
    ui->setupUi(this);
}

MyEvent::~MyEvent()
{
    delete ui;
}
