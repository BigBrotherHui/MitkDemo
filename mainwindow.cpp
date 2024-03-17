#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "ufunbase.h"
#include "ustatus.h"
#include <QPointer>
#include "QMessageBox"
#include <QCloseEvent>
#include "runtimeutil.h"
#include "systemtoolbar.h"
#include <QGraphicsBlurEffect>
#include "global.h"
#include "SqlDemo.h"
#include <QTimer>
#include "ureflect.h"
#include "CaseManage.h"
#include "CaseManageControl.h"
#include "NavigationWidget.h"
#include "NavigationWidgetControl.h"
#include "PreOperationDesignControl.h"
#include "RehearsalWidget.h"
#include "RehearsalWidgetControl.h"
#include "StdMultiWidget.h"
#include "SubToolBar.h"
#include "MainToolBar.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f_Init();
    RuntimeUtil::SetRunning(true);
    mTimer = new QTimer(this);
    connect(mTimer,&QTimer::timeout,this,&MainWindow::slot_timeout);
    mTimer->start();
}

void MainWindow::slot_timeout()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->label_time->setText(time);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMarkerVisible(bool v) {
    ui->label_robot->setVisible(v);
    ui->label_robot_2->setVisible(v);
    ui->label_robot_3->setVisible(v);
    ui->label_robot_4->setVisible(v);
    ui->label_robot_5->setVisible(v);
}

void MainWindow::SetCurrentCenterWidget(CenterWidget index)
{
    this->ui->stackedWidget->setCurrentWidget(m_centerWidgetMap[index]);
}

void MainWindow::SetCurrentControlWidget(ControlWidget index)
{
    this->ui->stackedWidget_control_right->setCurrentWidget(m_controlWidgetMap[index]);
}

void MainWindow::SetCurrentToolBar(ToolBarWidget index)
{
    this->ui->stackedWidget_topbar->setCurrentWidget(m_toolBarWidgetMap[index]);
}

QWidget* MainWindow::GetCenterWidget(CenterWidget index)
{
    return m_centerWidgetMap[index];
}

QWidget* MainWindow::GetControlWidget(ControlWidget index)
{
    return m_controlWidgetMap[index];
}

QWidget* MainWindow::GetToolBarWidget(ToolBarWidget index)
{
    return m_toolBarWidgetMap[index];
}

void MainWindow::f_Init()
{
    m_caseManage = new CaseManage(this);
    m_navigationWidget = new NavigationWidget(this);
    m_rehearsalWidget = new RehearsalWidget(this);
    m_stdMultiWidget = new StdMultiWidget(this);

    m_centerWidgetMap.emplace(CenterWidget_CaseManage, m_caseManage);
    m_centerWidgetMap.emplace(CenterWidget_NavigationWidget, m_navigationWidget);
    m_centerWidgetMap.emplace(CenterWidget_RehearWidget, m_rehearsalWidget);
    m_centerWidgetMap.emplace(CenterWidget_StdMultiWidget, m_stdMultiWidget);
    
    m_caseManageControl=new CaseManageControl(this);
    m_navigationWidgetControl=new NavigationWidgetControl(this);
    m_preOperationDesignControl=new PreOperationDesignControl(this);
    m_rehearsalWidgetControl=new RehearsalWidgetControl(this);

    m_controlWidgetMap.emplace(ControlWidget_CaseManageControl, m_caseManageControl);
    m_controlWidgetMap.emplace(ControlWidget_NavigationWidgetControl,m_navigationWidgetControl);
    m_controlWidgetMap.emplace(ControlWidget_PreOperationDesignControl, m_preOperationDesignControl);
    m_controlWidgetMap.emplace(ControlWidget_RehearsalWidgetControl,m_rehearsalWidgetControl);
    

    m_subToolBar=new SubToolBar(this);
    m_mainToolBar=new MainToolBar(this);
    m_toolBarWidgetMap.emplace(ToolBarWidget_MainToolBar, m_mainToolBar);
    m_toolBarWidgetMap.emplace(ToolBarWidget_SubToolBar,m_subToolBar);

    uStatus::mMain = this;

    this->ui->stackedWidget->addWidget(m_caseManage);
    this->ui->stackedWidget->addWidget(m_navigationWidget);
    this->ui->stackedWidget->addWidget(m_rehearsalWidget);
    this->ui->stackedWidget->addWidget(m_stdMultiWidget);
    this->ui->stackedWidget->setCurrentWidget(m_caseManage);

    this->ui->stackedWidget_control_right->addWidget(m_caseManageControl);
    this->ui->stackedWidget_control_right->addWidget(m_navigationWidgetControl);
    this->ui->stackedWidget_control_right->addWidget(m_preOperationDesignControl);
    this->ui->stackedWidget_control_right->addWidget(m_rehearsalWidgetControl);
    this->ui->stackedWidget_control_right->setCurrentWidget(m_caseManageControl);

    this->ui->stackedWidget_topbar->addWidget(m_subToolBar);
    this->ui->stackedWidget_topbar->addWidget(m_mainToolBar);
    this->ui->stackedWidget_topbar->setCurrentWidget(m_mainToolBar);

    for(auto iter : m_centerWidgetMap){
        uFunBase* base = dynamic_cast<uFunBase *>(iter.second);
        if (base)
            base->f_Init();
    }
    for (auto iter : m_controlWidgetMap) {
        uFunBase* base = dynamic_cast<uFunBase*>(iter.second);
        if (base)
            base->f_Init();
    }
    for (auto iter : m_toolBarWidgetMap) {
        uFunBase* base = dynamic_cast<uFunBase*>(iter.second);
        if (base)
            base->f_Init();
    }
}

void MainWindow::setPatientInfo(QString t)
{
    ui->label_patientInfo->setText(t);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (QMessageBox::No == QMessageBox::question(this, tr("提示"), tr("请确认是否退出？"), QMessageBox::Yes | QMessageBox::No))
    {
        e->ignore();
        return;
    }
    e->accept();
    RuntimeUtil::SetRunning(false);
}




