#include "RobotCommThread.h"
#include "./RobotController.h"

 RobotCommThread::RobotCommThread(RobotController *robot, QObject *parent)
	 : robotControler(robot)
 {
 }

 RobotCommThread::RobotCommThread(QObject *parent) 
 {
 
 }

RobotCommThread::~RobotCommThread()
{
}

void RobotCommThread::startThread()
{
	stopped.store(false);
	__super::start();

	do {
		QThread::msleep(10);
		qApp->processEvents();
	} while (!this->isRunning());
}

void RobotCommThread::stopThread()
{
	stopped.store(true);
	while (this->isRunning()) {
		QThread::msleep(100);
		qApp->processEvents();
	}

	__super::requestInterruption();
	__super::quit();
	__super::wait();
}

void RobotCommThread::run()
{


	while (!stopped.load()) {
		doWork();
		//processEvent(timeout, 500);
	}
}

void RobotCommThread::doWork()
{
	std::vector<int> states = { 0, 0 };
	bool flag = robotControler->getRobotState(states);
	if (flag == false) {
		states[0] = static_cast<int>(RobotState::ROBOT_EXCEPTION);
		states[1] = static_cast<int>(RobotErrorCode::ROBOT_UNCONNECTED_UPPC);
	}
	else {
		heartbeat.store(robotControler->hasHeartBeat());
		if (heartbeat.load()) {
			robotControler->getCurrentRobotJoint(robotJoint);
			robotControler->getCurrentRobotPose(e2bMatrix);
		}
	}
	
	if (robotState.load() != RobotState(states[0]) ) {	
		Q_EMIT signalRobotStateChanged(states[0]);
	}

// 	if (RobotState(states[0]) == RobotState::ROBOT_EXCEPTION) {
// 		if (RobotErrorCode(states[1]) != robotErrorCode.load()) {
// 			robotErrorCode.store(RobotErrorCode(states[1]));
// 			Q_EMIT signalRobotException(states[1]);
// 		}
// 	}

	if (robotState.load() != RobotState(states[0]) ||
		robotErrorCode.load() != RobotErrorCode(states[1])) {
		robotState.store(RobotState(states[0]));
		robotErrorCode.store(RobotErrorCode(states[1]));
	}



	std::string temp = std::string("RobotState: ") + std::to_string(states[0]) + std::string(", Error Code: ") + std::to_string(states[1]);
	//Logger::writeDebugLog(0, "RobotCommThread::doWork()", temp.c_str());
}
