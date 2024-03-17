#ifndef NAVIGATIONWIDGETCONTROL_H
#define NAVIGATIONWIDGETCONTROL_H

#include <QWidget>
#include "ufunbase.h"

namespace Ui {
class NavigationWidgetControl;
}

class NavigationWidgetControl : public uFunBase
{
    Q_OBJECT

public:

    Q_INVOKABLE explicit NavigationWidgetControl(QWidget *parent = nullptr);
    ~NavigationWidgetControl();
private:
    Ui::NavigationWidgetControl *ui;
};

#endif // NAVIGATIONWIDGETCONTROL_H
