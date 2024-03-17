#pragma once
#include "mitkCommon.h"
#include "mitkDataInteractor.h"

#include <mitkDataInteractor.h>
#include "mitkInteractionEvent.h"
class mitkInteractor : public mitk::DataInteractor
{
public:
    mitkClassMacro(mitkInteractor, mitk::DataInteractor);
    itkFactorylessNewMacro(Self);
    itkCloneMacro(Self);
    void AddCenter(mitk::StateMachineAction*, mitk::InteractionEvent*);
    void TestRightButtonClicked(mitk::StateMachineAction*, mitk::InteractionEvent*);
protected:
    mitkInteractor();
    ~mitkInteractor() override;

  void ConnectActionsAndFunctions() override;
};
