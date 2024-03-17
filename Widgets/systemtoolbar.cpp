#pragma execution_character_set("utf-8")
#include "systemtoolbar.h"
#include "ui_systemtoolbar.h"
#include <QDesktopWidget>
#include <QDateTime>
#include <QDebug>
#include "QMessageBox.h"
#include <QFileDialog>
#include <QScreen>
#include "runtimeutil.h"
#include <QMenu>
#include "usermanagerdialog.h"
SystemToolBar::SystemToolBar(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::SystemToolBar)
{
    ui->setupUi(this);
	ui->toolButton_settings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_settings->setPopupMode(QToolButton::InstantPopup);
    m_menu = new QMenu(this);
    m_actionUserManager = new QAction(this);
    m_actionUserManager->setText("用户管理");
    connect(m_actionUserManager,&QAction::triggered,this,&SystemToolBar::slot_userManager);
    m_menu->addAction(m_actionUserManager);
    ui->toolButton_settings->setMenu(m_menu);
}

SystemToolBar::~SystemToolBar()
{
    delete ui;
}

void SystemToolBar::slot_userManager() {
    UserManagerDialog dlg;
    dlg.exec();
}

void SystemToolBar::on_toolButton_settings_clicked()
{
	
}

void SystemToolBar::on_pushButton_screenshot_clicked()
{
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".bmp";
    QString selectedDir = QFileDialog::getSaveFileName(this, tr("保存截图"), "C:/Users/Administrator/Pictures/" + fileName, "BMP files (*.bmp)");
    if (selectedDir.isEmpty())
    {
        return;
    }
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QPixmap pix = QApplication::screens().first()->grabWindow(
                QApplication::desktop()->winId(),
                0, 0,
                screenGeometry.width(),
                screenGeometry.height()
                );
    if (pix.isNull())
    {
        QMessageBox::warning(this,"提示","截屏失败！");
        return;
    }
    if (!pix.save(selectedDir))
    {
        QMessageBox::warning(this,"提示","截屏保存失败！");
        return;
    }
    QMessageBox::warning(this,"提示",QString("截屏成功！文件保存在：%1").arg(selectedDir));
}

void SystemToolBar::on_pushButton_exit_clicked()
{
    if(QMessageBox::No == QMessageBox::question(this,"提示","是否退出程序？", QMessageBox::Yes | QMessageBox::No))
        return;
    RuntimeUtil::SetRunning(false);
    qApp->exit(0);
}
