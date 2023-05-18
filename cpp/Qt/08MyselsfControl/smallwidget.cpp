#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);


    //QSpinBox移动， QSlider跟着移动

    void(QSpinBox::* spBox)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, spBox, ui->horizontalSlider, &QSlider::setValue);

    //QSlider滑动， QSpinBox移动
    void(QSlider::* sliPtr)(int) = &QSlider::valueChanged;
    connect(ui->horizontalSlider, sliPtr,ui->spinBox, &QSpinBox::setValue);

}

SmallWidget::~SmallWidget()
{
    delete ui;
}

void SmallWidget::SetNum(int num)
{
    ui->spinBox->setValue(num);

}

int SmallWidget::GetNUm()
{
    return ui->spinBox->value();
}
