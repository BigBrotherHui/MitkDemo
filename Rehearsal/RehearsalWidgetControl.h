#ifndef REHEARSALWIDGETCONTROL_H
#define REHEARSALWIDGETCONTROL_H

#include <QWidget>
#include "ufunbase.h"
namespace Ui {
class RehearsalWidgetControl;
}

class RehearsalWidgetControl : public uFunBase
{
    Q_OBJECT

public:
    static int typeId;

    Q_INVOKABLE explicit RehearsalWidgetControl(QWidget *parent = nullptr);
    ~RehearsalWidgetControl();
    virtual void f_Init();

protected slots:
    void on_horizontalSlider_opacity_valueChanged(int);
    void on_pushButton_color_clicked();
private:
    Ui::RehearsalWidgetControl *ui;
};

#endif // REHEARSALWIDGETCONTROL_H
