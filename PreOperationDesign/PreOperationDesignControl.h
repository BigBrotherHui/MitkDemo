#ifndef PREOPERATIONDESIGNCONTROL_H
#define PREOPERATIONDESIGNCONTROL_H

#include <QWidget>
#include "ufunbase.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PreOperationDesignControl; }
QT_END_NAMESPACE

class PreOperationDesignControl : public uFunBase
{
    Q_OBJECT

public:
    
    Q_INVOKABLE PreOperationDesignControl(QWidget *parent = nullptr);
    ~PreOperationDesignControl();
private:
    Ui::PreOperationDesignControl *ui;
};
#endif // PREOPERATIONDESIGNCONTROL_H
