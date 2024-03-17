#include "SubToolBar.h"
#include "ui_SubToolBar.h"
#include <QDebug>
#include "ufunbase.h"
#include "ustatus.h"
#include "QMessageBox"
#include "global.h"
#include <QButtonGroup>

SubToolBar::SubToolBar(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::SubToolBar)
{
    ui->setupUi(this);
    mPage.emplace(Page_CaseManage, ui->pushButton_casemanage);
    mPage.emplace(Page_PreOperation_Design, ui->pushButton_design);
    mPage.emplace(Page_Demo, ui->pushButton_rehearsal);
    mPage.emplace(Page_Navigate, ui->pushButton_navigate);
    for (auto pair : mPage) {
        ui->buttonGroup->setId(pair.second, pair.first);
    }
}

SubToolBar::~SubToolBar()
{
    delete ui;
}

void SubToolBar::f_Refresh()
{
}

void SubToolBar::f_Init()
{
}

void SubToolBar::setCurrentPage(Page p)
{
    mPage[(int)p]->setChecked(1);
}

void SubToolBar::on_pushButton_casemanage_clicked()
{
    uStatus::mMain->SetCurrentCenterWidget(MainWindow::CenterWidget_CaseManage);
    uStatus::mMain->SetCurrentControlWidget(MainWindow::ControlWidget_CaseManageControl);
}

void SubToolBar::on_pushButton_design_clicked()
{
    uStatus::mMain->SetCurrentCenterWidget(MainWindow::CenterWidget_StdMultiWidget);
    uStatus::mMain->SetCurrentControlWidget(MainWindow::ControlWidget_PreOperationDesignControl);
}

void SubToolBar::on_pushButton_rehearsal_clicked()
{
    uStatus::mMain->SetCurrentCenterWidget(MainWindow::CenterWidget_RehearWidget);
    uStatus::mMain->SetCurrentControlWidget(MainWindow::ControlWidget_RehearsalWidgetControl);
}

void SubToolBar::on_pushButton_navigate_clicked()
{
    uStatus::mMain->SetCurrentCenterWidget(MainWindow::CenterWidget_NavigationWidget);
    uStatus::mMain->SetCurrentControlWidget(MainWindow::ControlWidget_NavigationWidgetControl);
}

void SubToolBar::on_buttonGroup_idClicked(int id)
{
    if (id < 0 || lastId==id)
        return;
    ui->label_title->setText(ui->buttonGroup->button(id)->text());
}
