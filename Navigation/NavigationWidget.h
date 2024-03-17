#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QWidget>
#include "ufunbase.h"

namespace Ui {
class NavigationWidget;
}

class NavigationWidget : public uFunBase
{
    Q_OBJECT

public:

    Q_INVOKABLE explicit NavigationWidget(QWidget *parent = nullptr);
    ~NavigationWidget();
private:
    Ui::NavigationWidget *ui;
};

#endif // NAVIGATIONWIDGET_H
