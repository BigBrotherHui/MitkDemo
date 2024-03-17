#pragma once
#include <QWidget>

class uFunBase: public QWidget
{
    Q_OBJECT
public:
    explicit uFunBase(QWidget *parent = 0);


    virtual int f_BeforeClose();
    virtual void f_Init();
    virtual void f_Update();
    virtual void f_Destroy();
    virtual void f_Close();
    virtual void f_Refresh();
    virtual void f_Switch();
    virtual void f_SetPparameter(QString pParameter);

protected:
};