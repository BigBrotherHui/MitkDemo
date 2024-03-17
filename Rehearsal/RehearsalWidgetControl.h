#ifndef REHEARSALWIDGETCONTROL_H
#define REHEARSALWIDGETCONTROL_H

#include <QWidget>
#include "ufunbase.h"
#include "mitkInteractor.h"

namespace Ui {
class RehearsalWidgetControl;
}

class RehearsalWidgetControl : public uFunBase
{
    Q_OBJECT

public:

    Q_INVOKABLE explicit RehearsalWidgetControl(QWidget *parent = nullptr);
    ~RehearsalWidgetControl();
    virtual void f_Init();
protected slots:
    void on_horizontalSlider_opacity_valueChanged(int);
    void on_pushButton_color_clicked();
    void on_pushButton_setInteractor_clicked();
    void on_pushButton_unsetInteractor_clicked();
private:
    Ui::RehearsalWidgetControl *ui;
    mitkInteractor::Pointer interactor{ nullptr };
};

#endif // REHEARSALWIDGETCONTROL_H
