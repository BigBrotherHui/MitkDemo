#ifndef ROBOT_COMM_THREAD_H
#define ROBOT_COMM_THREAD_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtCore/QTime>

#include <vector>

#include <Eigen/Dense>

#include "./RobotState.h"
//#include "../CommonLib/WorkerThreadLib/ManagerList.h"
//#include "../CommonLib/LogLib/Logger.h"
//#include "../Exception/Exception.h"

class RobotController;
class RobotCommThread : public QThread
{
    Q_OBJECT

public:
	explicit RobotCommThread(RobotController *robot, QObject *parent = nullptr);
	explicit RobotCommThread(QObject *parent = nullptr);
    ~RobotCommThread() override;

	void startThread();
	void stopThread();

	bool hasHeartBeat() { return heartbeat.load(); }

	RobotState getRobotState() { return { robotState.load()}; }
	RobotErrorCode getRobotError() { return robotErrorCode.load(); }

	std::vector<double> getRobotJoint() { return robotJoint; }
	//Eigen::Matrix4d getRobotPose() { return e2bMatrix; }
	
Q_SIGNALS:
	void signalRobotStateChanged(qint32);

protected:
	void run() override;
	void doWork();

protected:
	RobotController *robotControler = nullptr;

	std::atomic<RobotState> robotState{ RobotState::ROBOT_NONE };
	std::atomic<RobotErrorCode> robotErrorCode{ RobotErrorCode::ROBOT_EXCE_NONE };

	Eigen::Matrix4d e2bMatrix = Eigen::Matrix4d::Zero();

	std::vector<double> robotPose = {0};
	std::vector<double> robotJoint = {0};

	const int timeout = 1000;

	volatile std::atomic_bool  stopped{ true };
	volatile std::atomic_bool heartbeat{ false };

};

#endif // ROBOT_COMM_THREAD_H
