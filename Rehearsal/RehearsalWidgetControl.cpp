#include "RehearsalWidgetControl.h"
#include "ui_RehearsalWidgetControl.h"
#include "uStatus.h"
#include <mitkRenderingManager.h>
#include <QColorDialog>
#include <QDebug>
#include "usModule.h"
#include "usGetModuleContext.h"
#include <vtkSphereSource.h>
#include <mitkSurface.h>
RehearsalWidgetControl::RehearsalWidgetControl(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::RehearsalWidgetControl)
{
    ui->setupUi(this);
}

RehearsalWidgetControl::~RehearsalWidgetControl()
{
    delete ui;
}

void RehearsalWidgetControl::f_Init() {
    mitk::DataNode::Pointer node = uStatus::mDataStorage->GetNamedNode("DicomImage");
    if (node) {
        float color[3];
        node->GetColor(color);
        ui->pushButton_color->setStyleSheet(QString("background:rgb(%1,%2,%3);").arg(color[0]*255)
            .arg(color[2] * 255).arg(color[2] * 255));
        mitk::RenderingManager::GetInstance()->RequestUpdateAll();
    }
}

void RehearsalWidgetControl::on_horizontalSlider_opacity_valueChanged(int v) {
    double opa = v * 1. / 100;
    mitk::DataNode::Pointer node=uStatus::mDataStorage->GetNamedNode("DicomImage");
    if (!node)
        return;
    node->SetOpacity(opa);
    mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void RehearsalWidgetControl::on_pushButton_color_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->pushButton_color->setStyleSheet(QString("background:rgb(%1,%2,%3);").arg(color.red())
        .arg(color.green()).arg(color.blue()));
    float c[3];
    c[0] = color.red() * 1. / 255;
    c[1] = color.green() * 1. / 255;
    c[2] = color.blue() * 1. / 255;
    mitk::DataNode::Pointer node = uStatus::mDataStorage->GetNamedNode("DicomImage");
    if (!node)
        return;
    node->SetColor(c);
    mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void RehearsalWidgetControl::on_pushButton_setInteractor_clicked() {

    mitk::DataNode::Pointer node= uStatus::mDataStorage->GetNamedNode("testSurface");
    if (!node) {
        vtkSmartPointer< vtkSphereSource> ssource = vtkSmartPointer< vtkSphereSource>::New();
        ssource->SetRadius(20);
        ssource->SetPhiResolution(20);
        ssource->SetThetaResolution(20);
        ssource->Update();
        mitk::Surface::Pointer surface = mitk::Surface::New();
        surface->SetVtkPolyData(ssource->GetOutput());
        node = mitk::DataNode::New();
        node->SetData(surface);
        node->SetName("testSurface");
        node->SetColor(0, 1, 0);
        uStatus::mDataStorage->Add(node);
    }
    if(!interactor)
	    interactor = mitkInteractor::New();
    try
    {
		interactor->LoadStateMachine("TestInteraction.xml", us::GetModuleContext()->GetModule());
        interactor->SetEventConfig("TestConfig.xml", us::GetModuleContext()->GetModule());
		interactor->SetDataNode(node);
    }
    catch (std::exception &e)
    {
        std::cout << "exception:" << e.what() << std::endl;
    }
	mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void RehearsalWidgetControl::on_pushButton_unsetInteractor_clicked()
{
    if(interactor)
        interactor->SetDataNode(nullptr);
}
