#include "NavigationWidget.h"
#include "ui_NavigationWidget.h"

NavigationWidget::NavigationWidget(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::NavigationWidget)
{
    ui->setupUi(this);
}

NavigationWidget::~NavigationWidget()
{
    delete ui;
}
