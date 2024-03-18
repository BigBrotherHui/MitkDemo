#include "RobotUtility.h"

std::string RobotUtility::robotIp = "192.168.1.3";
int RobotUtility::robotPort = 50001;

RobotUtility::RobotUtility()
{
	//robotIp = Config::robotIp().toStdString();
	//robotPort = Config::robotPort();

    
	thread = new QThread();
	this->moveToThread(thread);
}

RobotUtility::~RobotUtility()
{

    RCF::deinit();
	if (thread) {
		thread->quit();
		thread->wait();
		thread->deleteLater();
	}
}

// bool RobotUtility::hasHeartBeat()
// {
// 	bool ret = false;
// 	std::vector<int> robotState = {0};
// 	getRobotStateByRCF(robotState);
// 	if (RobotState(robotState[0]) != RobotState::ROBOT_EXCEPTION) {
// 		ret = true;
// 	}
// 	else {
// 		Logger::writeErrorLog(0, "RobotUtility::hasHeartBeat()", "The robot is exception of RCF.");
// 	}
// 
// 	return ret;
// }
// 
// bool RobotUtility::getMoveArrivedStateByRCF()
// {
// 	bool arrivedState;
// 	try {
// 		RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
// 		arrivedState = client.getMoveArrivedState();
// 	}
// 	catch (const RCF::Exception &e) {
// 		Logger::writeErrorLog(0, "RobotUtility::getMoveArrivedStateByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
// 		return false;
// 	}
// 
// 	return arrivedState;
// }




bool RobotUtility::getCurrentRobotPoseByRCF(Eigen::Matrix4d &e2bMatrix)
{
   try {
       RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
       std::vector<double> matrix = client.getCurrentRobotPose();

       Q_ASSERT(matrix.size() == 16);

       e2bMatrix << matrix.at(0), matrix.at(1), matrix.at(2), matrix.at(3),
           matrix.at(4), matrix.at(5), matrix.at(6), matrix.at(7),
           matrix.at(8), matrix.at(9), matrix.at(10), matrix.at(11),
           matrix.at(12), matrix.at(13), matrix.at(14), matrix.at(15);
   }
   catch (const RCF::Exception &e) {
       Logger::writeErrorLog("RobotUtility::getCurrentRobotPoseByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
       return false;
   }

    return true;
}

bool RobotUtility::getCurrentRobotJointByRCF(std::vector<double> &joint)
{
   try {
       RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
       joint = client.getCurrentRobotJoint();

       Q_ASSERT(joint.size() == 7);

   }
   catch (const RCF::Exception &e) {
       //Logger::writeErrorLog(0, "RobotUtility::getCurrentRobotJointByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
       return false;
   }

    return true;
}



bool RobotUtility::startMoveByRCF(double speed, const std::vector<double> &targetPose)
{
    //Logger::writeInfoLog(0, "RobotUtility::startMoveByRCF()", "=== startMoveByRCF() begin ===");
    bool ret = false;

//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.startMove(speed, targetPose);
//    }
//    catch (const RCF::Exception & e) {
//        if (e.getErrorId() == 30) {	//timeout
//            ret = true;
//        }

//        //Logger::writeErrorLog(0, "RobotUtility::startMoveByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    //Logger::writeInfoLog(0, "RobotUtility::startMoveByRCF()", "=== startMoveByRCF() end ===");
    return ret;
}


bool RobotUtility::stopMoveByRCF(int retryCount)
{
    bool ret = false;

//    static std::atomic_bool isRunning = false;
//    try {
//        if (isRunning.load()) {
//            //Logger::writeInfoLog(0, "RobotUtility::stopMoveByRCF()", "@@@ The stopMoveByRCF() is running. @@@");
//            return ret;
//        }

//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));

//        //重试次数
//        int retry = 0;
//        std::atomic_bool isTimeout{ false };
//        while (!ret) {
//            isRunning.store(true);
//            ret = client.stopMove();

//            if (ret) {
//                //Logger::writeInfoLog(0, "RobotUtility::stopMoveByRCF()", "stop success");
//                break;
//            } // if stop successfully, break & process next

//            //timeout
//            if (retry > retryCount) {
//                isTimeout.store(true);
//                break;
//            }

//            retry++;
//            //Logger::writeInfoLog(0, "RobotUtility::stopMoveByRCF()", std::string(("@@@ retry times = ") + std::to_string(retry)).c_str());

//            //processEvent(100, 200);
//        }

//        isRunning.store(false);

//        if (isTimeout.load()) {
//            //Logger::writeInfoLog(0, "RobotUtility::stopMoveByRCF()", "@@@ The stopMoveByRCF() retry times have exceeded 3.  @@@");
//            return false;
//        }
//    }
//    catch (const RCF::Exception & e) {
//        isRunning.store(false);
//        //Logger::writeErrorLog(0, "RobotUtility::stopMoveByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::getRobotStateByRCF(std::vector<int> &state)
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        //client.getClientStub().setRemoteCallTimeoutMs(4000);
//        state = client.getRobotState();
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeDebugLog(0, "RobotUtility::getRobotStateByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//        return false;
//    }
    return true;
}

int RobotUtility::getSafetyStopStateByRCF()
{
    int ret = 3;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.getSafetyStopState();
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::getSafetyStopStateByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::rebootRobotByRCF()
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.rebootRobot();
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::rebootRobotByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::startDragByRCF(int dragSpace, int dragType)
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.startDrag(dragSpace, dragType);
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::startDragByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::stopDragByRCF()
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.stopDrag();
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::stopDragByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::setLoadByRCF(double loadMess, const std::vector<double> & loadCenter, const std::vector<double> & loadInertia)
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.setLoad(loadMess, loadCenter, loadInertia);
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::setLoadByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::setMotorPowerByRCF(int motorState)
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.setMotorPower(motorState);
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::setMotorPowerByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

bool RobotUtility::setJointLimitByRCF(const std::vector<double> &upperJointLimit, const std::vector<double> &lowerJointLimit, bool autoLimit)
{
    bool ret = false;
//    try {
//        RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
//        ret = client.setJointLimit(upperJointLimit, lowerJointLimit, autoLimit);
//    }
//    catch (const RCF::Exception & e) {
//        //Logger::writeErrorLog(0, "RobotUtility::setJointLimitByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
//    }

    return ret;
}

// int RobotUtility::getMotorStateByRCF()
// {
// 	int ret = 3;
// 	try {
// 		RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
// 		ret = client.getMotorState();
// 	}
// 	catch (const RCF::Exception & e) {
// 		//Logger::writeErrorLog(0, "RobotUtility::getMotorStateByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
// 	}
// 
// 	return ret;
// }



// bool RobotUtility::getRobotVersionByRCF(std::string & value)
// {
// 	bool ret = false;
// 	try {
// 		RcfClient<RobotRcfService> client(RCF::TcpEndpoint(robotIp, robotPort));
// 		ret = client.getRobotVersion(value);
// 	}
// 	catch (const RCF::Exception & e) {
// 		//Logger::writeErrorLog(0, "RobotUtility::getRobotVersionByRCF()", std::string("Error:" + e.getErrorMessage()).c_str());
// 	}
// 
// 	return ret;
// }




