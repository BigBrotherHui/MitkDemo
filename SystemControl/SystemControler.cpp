#include "SystemControler.h"
SystemControler* SystemControler::thisControler = nullptr;


SystemControler::SystemControler() : QObject()
{


	if (robotControler == nullptr) {
		robotControler = new RobotController(this);
	}

	if (robotCommThread == nullptr) {
		robotCommThread = new RobotCommThread(robotControler, this);
	}

}

SystemControler* SystemControler::getInstance()
{
	if (thisControler == nullptr) {
		thisControler = new SystemControler();
	}
	return thisControler;
}


SystemControler::~SystemControler()
{

	if (thisControler)
	{
		delete thisControler;
		thisControler = nullptr;
	}
}

void SystemControler::startThreads()
{

	robotCommThread->startThread();

}

void SystemControler::stopThreads()
{
	//Logger::writeInfoLog(0, "SystemControler::stopThreads()", "System all threads is stopping ................");



	if (robotCommThread) {
		robotCommThread->stopThread();
	}

}

void SystemControler::init(void)
{
	
}

void SystemControler::destory(void)
{
	
}
