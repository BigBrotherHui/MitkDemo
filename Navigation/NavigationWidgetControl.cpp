#include "NavigationWidgetControl.h"
#include "ui_NavigationWidgetControl.h"

NavigationWidgetControl::NavigationWidgetControl(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::NavigationWidgetControl)
{
    ui->setupUi(this);
}

NavigationWidgetControl::~NavigationWidgetControl()
{
    delete ui;
}
