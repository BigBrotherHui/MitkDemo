#ifndef ROBOT_COMM_UTILITY_H
#define ROBOT_COMM_UTILITY_H

#include <vector>
#include <iostream>

#include <Eigen/Dense>

#include <QThread>
#include <QApplication>
#include <QtCore/QDebug>
#include <QtCore/QObject>

#include "RobotRcfInterface.h"
#include "Logger.h"
class RobotUtility : public QObject
{
	Q_OBJECT
public:
	RobotUtility();
	~RobotUtility();

    static bool startMoveByRCF(double speed, const std::vector<double> &targetPose);
    static bool stopMoveByRCF(int retryCount);
    static bool getCurrentRobotPoseByRCF(Eigen::Matrix4d & e2bMatrix);
    static bool getCurrentRobotJointByRCF(std::vector<double> &joint);
    static bool getRobotStateByRCF(std::vector<int> &state);
    static int  getSafetyStopStateByRCF();
    static bool rebootRobotByRCF();
    static bool startDragByRCF(int dragSpace, int dragType);
    static bool stopDragByRCF();
    static bool setLoadByRCF(double loadMess, const std::vector<double> & loadCenter, const std::vector<double> & loadInertia);
    static bool setMotorPowerByRCF(int motorState);
    static bool setJointLimitByRCF(const std::vector<double> &, const std::vector<double> &, bool);
	
	
public Q_SLOTS:

private:
	static std::string robotIp;
	static int robotPort;

	QThread *thread;
};

#endif		//ROBOT_COMM_UTILITY_H
