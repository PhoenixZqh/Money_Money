#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QSlider>

namespace Ui {
class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = nullptr);
    ~SmallWidget();

    void SetNum(int num);
    int GetNUm();

private:
    Ui::SmallWidget *ui;
};

#endif // SMALLWIDGET_H
