#include "SubToolBar.h"
#include "ui_SubToolBar.h"
#include <QDebug>
#include "ufunbase.h"
#include "ufunction.h"
#include "ustatus.h"
#include "umainfunbase.h"
#include "QMessageBox"
#include "global.h"
#include <QButtonGroup>

int SubToolBar::typeId = qRegisterMetaType<SubToolBar*>();

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
    uMainFunBase* mMainFunBase = uFunction::getInStance()->f_GetMain();
    mMainFunBase->f_Open_Center("CaseManage");
    mMainFunBase->f_OpenControl_right("CaseManageControl");
}

void SubToolBar::on_pushButton_design_clicked()
{
    uMainFunBase* mMainFunBase = uFunction::getInStance()->f_GetMain();
    mMainFunBase->f_Open_Center("StdMultiWidget");
    mMainFunBase->f_OpenControl_right("PreOperationDesignControl");
}

void SubToolBar::on_pushButton_rehearsal_clicked()
{
    uMainFunBase* mMainFunBase = uFunction::getInStance()->f_GetMain();
    mMainFunBase->f_Open_Center("RehearsalWidget");
    mMainFunBase->f_OpenControl_right("RehearsalWidgetControl");
}

void SubToolBar::on_pushButton_navigate_clicked()
{
    uMainFunBase* mMainFunBase = uFunction::getInStance()->f_GetMain();
    mMainFunBase->f_Open_Center("NavigationWidget");
    mMainFunBase->f_OpenControl_right("NavigationWidgetControl");
}

void SubToolBar::on_buttonGroup_idClicked(int id)
{
    if (id < 0 || lastId==id)
        return;
    //ui->label_title->setText(ui->buttonGroup->button(id)->text());
}
