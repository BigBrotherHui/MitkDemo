#include "RehearsalWidget.h"
#include "ui_RehearsalWidget.h"
#include <mitkBaseRenderer.h>

RehearsalWidget::RehearsalWidget(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::RehearsalWidget)
{
    ui->setupUi(this);
    ui->widget->GetRenderer()->SetMapperID(mitk::BaseRenderer::Standard3D);
    m_dataStorage = mitk::StandaloneDataStorage::New();
    ui->widget->GetRenderer()->SetDataStorage(m_dataStorage);
}

RehearsalWidget::~RehearsalWidget()
{
    delete ui;
}
