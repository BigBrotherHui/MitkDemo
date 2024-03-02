#include "PreOperationDesignControl.h"
#include "./ui_PreOperationDesignControl.h"
int PreOperationDesignControl::typeId = qRegisterMetaType<PreOperationDesignControl*>();

PreOperationDesignControl::PreOperationDesignControl(QWidget *parent)
    : uFunBase(parent)
    , ui(new Ui::PreOperationDesignControl)
{
    ui->setupUi(this);
}

PreOperationDesignControl::~PreOperationDesignControl()
{
    delete ui;
}

