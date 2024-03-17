#include "userinputdialog.h"
#include "ui_userinputdialog.h"
#include "ustatus.h"
#include "SqlDemo.h"
#include "qmessagebox.h"
#include "global.h"
#include <QDebug>
UserInputDialog::UserInputDialog(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::UserInputDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::SubWindow);
    setWindowFlag(Qt::FramelessWindowHint);
    ui->widget->setTitle("添加用户");
    ui->pushButton_add->setDefault(true);
    ui->pushButton_add->setFixedSize(96,34);

    ui->pushButton_close->setFixedSize(96,34);
}

UserInputDialog::~UserInputDialog()
{
    delete ui;
}

void UserInputDialog::on_pushButton_add_clicked()
{
    QString id=ui->lineEdit_id->text();
    QString password=ui->lineEdit_password->text();
    if(!IsValidId(id))
    {
        QMessageBox::warning(this,"提示","账号规则：不超过20位，不以下划线开头，不包含@#$%^&*及中文字符！");
        return;
    }
    if(!IsValidPassword(password))
    {
        QMessageBox::warning(this,"提示","密码规则：大于6位，包含英文字符和数字，不包含@#$%^&*及中文字符！");
        return;
    }
    user_info info;
    info.id=id;
    info.name=ui->lineEdit_name->text();
    info.password=password;
    info.sex=ui->comboBox_sex->currentIndex();
    info.authority=ui->comboBox_authority->currentIndex();
    info.enable=ui->comboBox_enable->currentIndex();
    bool isExisted{false};
    bool ret=uStatus::mSql->IsUserExisted(info.id,isExisted);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","查询用户是否存在失败！");
        return;
    }
    if(isExisted)
    {
        QMessageBox::warning(this,"提示","用户名已存在！请重新输入用户名！");
        return;
    }
    ret=uStatus::mSql->AddUser(info);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","添加用户失败！请联系管理员！");
        reject();
        close();
    }
    QMessageBox::warning(this,"提示","添加用户成功！");
    accept();
    close();
}

void UserInputDialog::on_pushButton_close_clicked()
{
    close();
}
