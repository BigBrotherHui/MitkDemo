#include <QDebug>
#include <QVBoxLayout>

#include "ustatus.h"
#include "StdMultiWidget.h"
#include "ui_StdMultiWidget.h"
#include "QmitkStdMultiWidget.h"
#include "QmitkLevelWindowWidget.h"
#include <QmitkRenderWindow.h>
class vtkMyCallback : public vtkCommand
{
public:
    static vtkMyCallback* New() { return new vtkMyCallback; }

    vtkMyCallback()
    {
    }

    ~vtkMyCallback()
    {

    }

    virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData)
    {
        std::cout << "Execute" << std::endl;
    }
};

StdMultiWidget::StdMultiWidget(QWidget *parent) :
    uFunBase(parent),
    ui(new Ui::StdMultiWidget)
{
    ui->setupUi(this);

    qDebug()<<"StdMultiWidget: create!";
}

StdMultiWidget::~StdMultiWidget()
{
    delete ui;
}

void StdMultiWidget::f_Init()
{
    qDebug()<<"StdMultiWidget: Init!";
    if (uStatus::mDataStorage == nullptr)
    {
        return ;
    }


    vlayout = new QVBoxLayout(ui->widget);
    vlayout->setMargin(0);
    vlayout->setSpacing(1);

    // Create viewParent widget with horizontal layout
    viewParent = new QWidget(ui->widget);
    vlayout->addWidget(viewParent);
    hlayout = new QHBoxLayout(viewParent);
    hlayout->setMargin(0);

    multiWidget =std::unique_ptr<QmitkStdMultiWidget>( new QmitkStdMultiWidget(viewParent));

    hlayout->addWidget(multiWidget.get());

    multiWidget->SetDataStorage(uStatus::mDataStorage);

    multiWidget->InitializeMultiWidget();
    multiWidget->AddPlanesToDataStorage();

    multiWidget->SetWidgetPlanesVisibility(false, multiWidget->GetRenderWindow4()->GetRenderer());
    multiWidget->SetCrosshairGap(0);

    vtkSmartPointer<vtkMyCallback> m_callback = vtkSmartPointer<vtkMyCallback>::New();
    multiWidget->GetRenderWindow4()->interactor()->AddObserver(vtkCommand::LeftButtonPressEvent, m_callback);
    hlayout->setStretchFactor(multiWidget.get(),100);

    
}

void StdMultiWidget::f_Destroy()
{
    multiWidget->RemovePlanesFromDataStorage();
    multiWidget->ActivateMenuWidget(false);

    multiWidget.release();
    multiWidget.reset();
    //levelWindowWidget.release();
    //levelWindowWidget.reset();
    delete hlayout;
    delete viewParent;
    delete vlayout;
}

int StdMultiWidget::f_BeforeClose()
{
    qDebug() << "StdMultiWidget::f_BeforeClose() ... ...";
    f_Destroy();
    f_Close();
    return 0;
}
void StdMultiWidget::f_Close()
{
    this->close();
}

void StdMultiWidget::f_Reset()
{
    this->multiWidget->ResetCrosshair();
}

QmitkStdMultiWidget *StdMultiWidget::GetMultiWidget()
{
    if(multiWidget)
    {
        return multiWidget.get();
    }
}
