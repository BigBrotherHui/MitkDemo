#include "ureflect.h"
#include "CaseManage.h"
#include "CaseManageControl.h"
#include "NavigationWidget.h"
#include "NavigationWidgetControl.h"
#include "PreOperationDesignControl.h"
#include "RehearsalWidget.h"
#include "RehearsalWidgetControl.h"
#include "StdMultiWidget.h"
#include "SubToolBar.h"
#include "mainframe.h"
#include "MainToolBar.h"
void uReflect::registerAllClasses(){
	registerClass<CaseManage>();
	registerClass<CaseManageControl>();
	registerClass<NavigationWidget>();
	registerClass<NavigationWidgetControl>();
	registerClass<PreOperationDesignControl>();
	registerClass<RehearsalWidget>();
	registerClass<RehearsalWidgetControl>();
	registerClass<StdMultiWidget>();
	registerClass<SubToolBar>();
	registerClass<MainFrame>();
	registerClass<MainToolBar>();
}