#ifndef USERINPUTDIALOG_H
#define USERINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class UserInputDialog;
}

class UserInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserInputDialog(QWidget *parent = nullptr);
    ~UserInputDialog();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::UserInputDialog *ui;
};

#endif // USERINPUTDIALOG_H
