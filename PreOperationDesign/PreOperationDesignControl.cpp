#include "PreOperationDesignControl.h"
#include "./ui_PreOperationDesignControl.h"
#include "ureflect.h"

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

