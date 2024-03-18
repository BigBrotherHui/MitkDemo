#ifndef USERMANAGERDIALOG_H
#define USERMANAGERDIALOG_H

#include <QDialog>
#include "SqlDemo.h"
namespace Ui {
class UserManagerDialog;
}

class UserManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagerDialog(QWidget *parent = nullptr);
    ~UserManagerDialog();
    void RefreshTable(const std::vector<user_info> &pTuples);
protected:
    void RefreshTable();
private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_enable_clicked();

    void on_pushButton_disable_clicked();

    void on_pushButton_resetPassword_clicked();

private:
    Ui::UserManagerDialog *ui;
};

#endif // USERMANAGERDIALOG_H
