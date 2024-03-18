#include "usermanagerdialog.h"
#include "ui_usermanagerdialog.h"
#include <QTextCodec>
#include "CaseManage.h"
#include "userinputdialog.h"
#include "QMessageBox.h"
UserManagerDialog::UserManagerDialog(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::UserManagerDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::SubWindow);
    ui->widget->setTitle("用户管理");
    RefreshTable();
}

UserManagerDialog::~UserManagerDialog()
{
    delete ui;
}

void UserManagerDialog::RefreshTable(const std::vector<user_info> &pTuples)
{
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setFixedHeight(40);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QStringList headerlabels{
        codec->toUnicode("账号 ")
       , codec->toUnicode("用户名")
       , codec->toUnicode("密码")
       , codec->toUnicode("性别")
       , codec->toUnicode("权限")
       , codec->toUnicode("可用状态")};
    ui->tableWidget->setColumnCount(headerlabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerlabels);
    for (size_t i = 0; i < pTuples.size(); i++)
    {
        user_info info=pTuples.at(i);
        if(info.id==LOGIN_ID_ADMIN)
            continue;
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(info.id));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(info.name));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(info.password));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(info.sex==Sex_Male?"男":"女"));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(info.authority==Authority_Admin?"管理员":"普通用户"));
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(info.enable==Enable_Able?"可用":"不可用"));
        for (int j = 0; j < headerlabels.size(); j++)
        {
            ui->tableWidget->item(0, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void UserManagerDialog::RefreshTable()
{
    std::vector<user_info> info;
    bool ret=uStatus::mSql->GetUserByAuthority(info,Authority_Admin);
    if(ret)
    {
        RefreshTable(info);
    }
}

void UserManagerDialog::on_pushButton_add_clicked()
{
    UserInputDialog d(this);
    if(d.exec()==QDialog::Accepted)
    {
        RefreshTable();
    }
}

void UserManagerDialog::on_pushButton_del_clicked()
{
    QList<QTableWidgetItem *> items=ui->tableWidget->selectedItems();
    int selectedItemSize=items.size();
    if(selectedItemSize==0)
    {
        QMessageBox::warning(this,"提示","请先选中待删除的用户！");
        return;
    }
    QString id=items.at(0)->text();
    bool ret=uStatus::mSql->RemoveUserById(id);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","删除用户失败！");
        return;
    }
    RefreshTable();
    QMessageBox::warning(this,"提示","删除成功！");
}

void UserManagerDialog::on_pushButton_enable_clicked()
{
    QList<QTableWidgetItem *> items=ui->tableWidget->selectedItems();
    int selectedItemSize=items.size();
    if(selectedItemSize==0)
    {
        QMessageBox::warning(this,"提示","请先选中用户！");
        return;
    }
    QString id=items.at(0)->text();
    bool ret=uStatus::mSql->SetUserEnableById(id,Enable_Able);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","用户启用失败！");
        return;
    }
    RefreshTable();
    QMessageBox::warning(this,"提示","启用成功！");
}

void UserManagerDialog::on_pushButton_disable_clicked()
{
    QList<QTableWidgetItem *> items=ui->tableWidget->selectedItems();
    int selectedItemSize=items.size();
    if(selectedItemSize==0)
    {
        QMessageBox::warning(this,"提示","请先选中用户！");
        return;
    }
    QString id=items.at(0)->text();
    bool ret=uStatus::mSql->SetUserEnableById(id,Enable_Disable);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","用户停用失败！");
        return;
    }
    RefreshTable();
    QMessageBox::warning(this,"提示","停用成功！");
}

void UserManagerDialog::on_pushButton_resetPassword_clicked()
{
    QList<QTableWidgetItem *> items=ui->tableWidget->selectedItems();
    int selectedItemSize=items.size();
    if(selectedItemSize==0)
    {
        QMessageBox::warning(this,"提示","请先选中用户！");
        return;
    }
    if(QMessageBox::No ==QMessageBox::question(this,"提示","确定重置该用户的密码吗？", QMessageBox::Yes | QMessageBox::No))
        return;
    QString id=items.at(0)->text();
    QString encryptPassword=SqlDemo::encryptPassword(DEFAULT_PASSWORD);
    bool ret=uStatus::mSql->UpdateUserPasswordById(id,encryptPassword);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","重置密码失败！");
        return;
    }
    QMessageBox::warning(this,"提示","重置成功！");
}
