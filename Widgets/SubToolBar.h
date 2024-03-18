
#ifndef SubToolBar_H
#define SubToolBar_H

#include <QWidget>
#include "ufunbase.h"
#include <QtCore/qobjectdefs.h>
#include <QPushButton>


class QWidget;

namespace Ui
{
class SubToolBar;
}

class SubToolBar : public uFunBase
{
    Q_OBJECT

public:
    enum Page {
        Page_CaseManage=0,
        Page_PreOperation_Design,
        Page_Demo,
        Page_Navigate
    };
    Q_INVOKABLE explicit SubToolBar(QWidget *parent = nullptr);
    ~SubToolBar();
    void f_Refresh() override;
    void f_Init() override;
    void setCurrentPage(Page p);
private slots:
    void on_pushButton_casemanage_clicked();
    void on_pushButton_design_clicked();
    void on_pushButton_rehearsal_clicked();
    void on_pushButton_navigate_clicked();
    void on_buttonGroup_idClicked(int id);
private:
    Ui::SubToolBar *ui;
    int lastId{ -1 };
    std::map<int, QPushButton*> mPage;
};

#endif // SubToolBar_H
