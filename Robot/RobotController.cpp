#include "RobotController.h"

RobotController::RobotController(QObject *parent) : ControllerBase()
{
	init();
}

RobotController::~RobotController()
{
	destroy();
}

bool RobotController::hasHeartBeat()
{
	if (currRobotState.load() == RobotState::ROBOT_EXCEPTION &&
		currRobotErrorCode.load() == RobotErrorCode::ROBOT_UNCONNECTED_UPPC)	{
		return false;
	} 
	else {
		return true;
	}
}



bool RobotController::getRobotState(std::vector<int> &state)
{
	bool ret = robotUtility->getRobotStateByRCF(state);
	if (ret) {
		if (currRobotState.load() != static_cast<RobotState>(state[0])) {
			currRobotState.store(static_cast<RobotState>(state[0]));
			currRobotErrorCode.store(static_cast<RobotErrorCode>(state[1]));
			//Logger::writeDebugLog(0, "RobotController::getRobotState()", (std::string("Robot's state is ") + std::to_string(int(currRobotState.load()))).c_str());
		}
	}
	else {
		currRobotState.store(RobotState::ROBOT_EXCEPTION);
		currRobotErrorCode.store(RobotErrorCode::ROBOT_UNCONNECTED_UPPC);
	}

	return ret;
}

bool RobotController::checkMoveCondition()
{
	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON/* && robotUtility.setArrivedStateByRCF(false)*/) {
		return true;
	}
	else {
		//Logger::writeErrorLog(0, "RobotController::checkMoveCondition()", "please check robot connect or motor");
		return false;
	}
}

void RobotController::init()
{
	robotUtility = std::make_unique<RobotUtility>();
	
	this->setMotorPower(1);
// 	const std::vector<double> &upperJointLimit = { 163, 113, 163, 113, 163, 113, 353 };
// 	const std::vector<double> &lowerJointLimit = { -163,-113,-163,-113,-163,-113,-353 };
// 	this->setJointLimit(upperJointLimit, lowerJointLimit, true);
}

void RobotController::reset()
{
}

void RobotController::destroy()
{
	this->setMotorPower(0);
}

bool RobotController::moveToInitPosition(double speed)
{
// 	std::vector<double> initPose = {};
// 	QStringList initPosConf = Config::initPos();
// 	for (int i = 0; i < initPosConf.size(); i++)
// 		initPose.push_back(initPosConf[i].toDouble());
// 
// 	Q_ASSERT(initPose.size() == 7);
// 	return moveJ2TargetPosition(initPose, speed);

	return true;
}

bool RobotController::moveToTransportPosition(double speed)
{
// 	std::vector<double> transportPose = {};
// 	QStringList transportPosConf = Config::transportPos();
// 	for (int i = 0; i < transportPosConf.size(); i++)
// 		transportPose.push_back(transportPosConf[i].toDouble());
// 
// 	Q_ASSERT(transportPose.size() == 7);
// 	return moveJ2TargetPosition(transportPose, speed);
	return true;
}

bool RobotController::moveToAcquireMiddlePosition(double speed)
{
// 	std::vector<double> acquirePose = {};
// 	QStringList acquirePosConf = Config::collectMiddlePos();
// 	for (int i = 0; i < acquirePosConf.size(); i++)
// 		acquirePose.push_back(acquirePosConf[i].toDouble());
// 
// 	Q_ASSERT(acquirePose.size() == 7);
// 	return moveJ2TargetPosition(acquirePose, speed);
	return true;
}

bool RobotController::moveToAcquirePosition(double speed)
{
// 	std::vector<double> acquirePose = {};
// 	QStringList acquirePosConf = Config::collectPos();
// 	for (int i = 0; i < acquirePosConf.size(); i++)
// 		acquirePose.push_back(acquirePosConf[i].toDouble());
// 
// 	Q_ASSERT(acquirePose.size() == 7);
// 	return moveJ2TargetPosition(acquirePose, speed);
	return true;
}



bool RobotController::moveJ2TargetPosition(const std::vector<double> &startPose, const double speed)
{
	Q_ASSERT(startPose.size() == 7);
	return this->startMove(speed, startPose);
}

bool RobotController::moveJ2TargetPosition(const std::array<double, 7> &startPose, const double speed)
{
	std::vector<double> targetPose(7);
	std::copy_n(startPose.begin(), startPose.size(), targetPose.begin());
	return this->startMove(speed, targetPose);
}

bool RobotController::moveL2TargetPosition(const std::array<double, 16> &startPose, const double speed)
{
	std::vector<double> targetPose(16);
	std::copy_n(startPose.begin(), startPose.size(), targetPose.begin());
	return this->startMove(speed, targetPose);
}

bool RobotController::pauseMove()
{
	//Logger::writeErrorLog(0, "RobotController::pauseMove()", std::to_string((int)currRobotState.load()).c_str());
	if (!this->hasHeartBeat()) {
		return false;
	}

	if (this->stopMove()) {
		return true;
	}
	else {
		//Logger::writeErrorLog(0, "RobotController::pauseMove()", "please check robot moving or motor");
		return false;
	}
}

bool RobotController::isArrivedAcquirePos()
{
// 	bool arrivedState = robotUtility->getMoveArrivedStateByRCF();
// 	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON && arrivedState) {
// 		return true;
// 	}
	return false;
}

bool RobotController::isArrivedAssemblePos()
{
// 	bool arrivedState = robotUtility->getMoveArrivedStateByRCF();
// 	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON && arrivedState) {
// 		return true;
// 	}
	return false;
}

bool RobotController::isArrivedPreparePos()
{
// 	bool arrivedState = robotUtility->getMoveArrivedStateByRCF();
// 	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON && arrivedState) {
// 		return true;
// 	}
	return false;
}

bool RobotController::isArrivedInitPos()
{
// 	bool arrivedState = robotUtility->getMoveArrivedStateByRCF();
// 	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON && arrivedState) {
// 		return true;
// 	}
	return false;
}

bool RobotController::isArrivedTargetPos()
{
// 	bool arrivedState = robotUtility->getMoveArrivedStateByRCF();
// 	if (currRobotState.load() == RobotState::ROBOT_CONNECTED_MOTOR_ON && arrivedState) {
// 		return true;
// 	}
	return false;
}

bool RobotController::isException()
{
	return currRobotState.load() == RobotState::ROBOT_EXCEPTION;
}

bool RobotController::startMove(double speed, const std::vector<double> &targetPose)
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->startMoveByRCF(speed, targetPose);
}

bool RobotController::stopMove()
{
	bool ret = false;
	/*
	if (!hasHeartBeat()) {
		Logger::writeInfoLog(0, "RobotController::stopMove()", "The hasHeartBeat() is stop.");
		return ret;
	}
	*/

	//ret = robotUtility->stopMoveThread();

	//Logger::writeInfoLog(0, "RobotController::stopMove()", "stop move");
	return ret;
}

bool RobotController::getCurrentRobotPose(Eigen::Matrix4d &e2bMatrix)
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->getCurrentRobotPoseByRCF(e2bMatrix);
}

bool RobotController::getCurrentRobotJoint(std::vector<double> &joint)
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->getCurrentRobotJointByRCF(joint);
}

int RobotController::getSafetyStopState()
{
	return robotUtility->getSafetyStopStateByRCF();
}

bool RobotController::rebootRobot()
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->rebootRobotByRCF();
}

bool RobotController::startDrag(int dragSpace, int dragType)
{
	if (!hasHeartBeat()) {
		return false;
	}
	//Logger::writeInfoLog(0, "RobotController::startDrag()", "start drag");
	return robotUtility->startDragByRCF(dragSpace, dragType);
}

bool RobotController::stopDrag()
{
	if (!hasHeartBeat()) {
		return false;
	}
	//Logger::writeInfoLog(0, "RobotController::stopDrag()", "stop drag");
	return robotUtility->stopDragByRCF();
}

bool RobotController::setLoad(double loadMess, const std::vector<double> &loadCenter, const std::vector<double> &loadInertia)
{
	if (!hasHeartBeat()) {
		return false;
	}

	return robotUtility->setLoadByRCF(loadMess, loadCenter, loadInertia);
}

bool RobotController::setMotorPower(int motorState)
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->setMotorPowerByRCF(motorState);
}

bool RobotController::setJointLimit(const std::vector<double> &upperJointLimit, const std::vector<double> &lowerJointLimit, bool autoLimit)
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	return robotUtility->setJointLimitByRCF(upperJointLimit, lowerJointLimit, autoLimit);
}

int RobotController::getMotorState()
{
	//return robotUtility->getMotorStateByRCF();
	return 1;
}




bool RobotController::getRobotVersion()
{
	if (!this->hasHeartBeat()) {
		return false;
	}

	std::string  robotVer = "";
	//bool val = robotUtility->getRobotVersionByRCF(robotVer);
	//Q_EMIT signalRobotVersion(QString::fromStdString(robotVer));
	return false;
}


