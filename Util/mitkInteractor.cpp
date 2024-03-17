#include "mitkInteractor.h"
#include <QDebug>
#include "mitkMouseMoveEvent.h"
#include "mitkDispatcher.h"
#include "mitkBaseRenderer.h"
#include <mitkDataInteractor.h>
#include <mitkInteractionConst.h>
#include "mitkInteractionEvent.h"
#include <mitkSurface.h>
#include <mitkInteractionPositionEvent.h>
void mitkInteractor::AddCenter(mitk::StateMachineAction*, mitk::InteractionEvent* interactionEvent)
{
	auto* positionEvent = dynamic_cast<mitk::InteractionPositionEvent*>(interactionEvent);
	if (!positionEvent)
		return;
	mitk::Point3D itkPoint = positionEvent->GetPositionInWorld();
	mitk::DataNode::Pointer node = GetDataNode();
	mitk::Surface::Pointer surface = dynamic_cast<mitk::Surface *>(node->GetData());
	if (!surface)
		return;
	vtkSmartPointer<vtkMatrix4x4> vmt = vtkSmartPointer<vtkMatrix4x4>::New();
	vmt->SetElement(0, 3, itkPoint[0]);
	vmt->SetElement(1, 3, itkPoint[1]);
	vmt->SetElement(2, 3, itkPoint[2]);
	surface->GetGeometry()->SetIndexToWorldTransformByVtkMatrix(vmt);
	mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void mitkInteractor::TestRightButtonClicked(mitk::StateMachineAction*, mitk::InteractionEvent*)
{
	qDebug() << "RightButtonClicked";
}

mitkInteractor::mitkInteractor()
{

}

mitkInteractor::~mitkInteractor()
{

}

void mitkInteractor::ConnectActionsAndFunctions()
{
	CONNECT_FUNCTION("addCenter", AddCenter);
	CONNECT_FUNCTION("test", TestRightButtonClicked);
}
