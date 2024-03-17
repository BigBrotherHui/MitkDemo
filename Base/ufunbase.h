#pragma once
#include <QWidget>

class uFunBase: public QWidget
{
    Q_OBJECT
public:
    explicit uFunBase(QWidget *parent = 0);

    QString mID = "";
    QString mInstensName = "";
    QString mType="C";
    //
    QString f_GetType();
    void f_SetType(QString pType);


    virtual int f_BeforeClose();

    //
    virtual QString f_GetID();
    virtual void f_Init();
    virtual void f_Update();
    virtual void f_Destroy();
    virtual void f_Close();
    virtual void f_Refresh();
    virtual void f_Switch();
    virtual void f_SetPparameter(QString pParameter);
    void f_SetInstensName(QString pInstensName);
    QString f_GetInstensName();

protected:
};