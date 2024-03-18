#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include <QtCore/QObject>

#include <Eigen/Dense>

#include "RobotState.h"
#include "Robot/RobotUtility.h"
#include "ControllerBase.h"
class RobotController : public ControllerBase
{
	Q_OBJECT

public:
	explicit RobotController(QObject *parent = nullptr);
	virtual ~RobotController() ;

	void init() override;
	void reset() override;
	void destroy() override;

	//可以调用RCF接口，返回true，否则返回false
	bool hasHeartBeat() override;

	bool isException() override;

public:
	//移动到初始位
	bool moveToInitPosition(double speed);

	//移动到运输位
	bool moveToTransportPosition(double speed);

	//移动到采集位
	bool moveToAcquirePosition(double speed);

	bool moveToAcquireMiddlePosition(double speed);

	//移动到指定目标位
	bool moveJ2TargetPosition(const std::vector<double> &startPose, const double speed);
	bool moveJ2TargetPosition(const std::array<double, 7> &startPose, const double speed);
	bool moveL2TargetPosition(const std::array<double, 16> &startPose, const double speed);

	//暂停移动
	bool pauseMove();

	bool isArrivedAssemblePos();
	bool isArrivedAcquirePos();
	bool isArrivedPreparePos();
	bool isArrivedInitPos();
	bool isArrivedTargetPos();


	/**
	 * 获取当前机器人位姿.
	 * @param[in] 机器人当前位姿
	 * @return true代表获取到，false代表机器人异常
	 */
	bool getCurrentRobotPose(Eigen::Matrix4d &e2bMatrix);

	/**
	 * 获取当前机器人关节角.
	 * @param[in] 机器人当前关节角
	 * @return true代表获取到，false代表机器人异常
	 */
	bool getCurrentRobotJoint(std::vector<double> &joint);

	/**
	 * 获取当前机器人当前运行状态.
	 * @return 机器人当前运行状态
	 */
	bool getRobotState(std::vector<int> &state);

	RobotState getRobotState() { return currRobotState.load(); };
	RobotErrorCode getRobotExceptionState() { return currRobotErrorCode.load(); };

	/**
	 * 获取机器人急停状态，分为安全门急停和急停按钮急停
	 * @return 1 无急停； 2 ESTOP； 3 GSTOP
	 */
	int getSafetyStopState();

	/**
	 * 重启机器人.
	 * @return 1 无急停； 2 ESTOP； 3 GSTOP
	 */
	bool rebootRobot();

	/**
	 * 开启拖动模式.
	 * 拖动空间：1 轴空间拖动； 2 笛卡尔空间拖动。
	 * 拖动类型：1 仅平移；2 仅旋转；3 自由拖动。
	 * @return  s
	 */
	bool startDrag(int dragSpace,int dragType);

	/**
     * 关闭拖动
	 *
	 * @throw CommandException 控制器返回设置失败.
	 * @throw NetworkException 网络连接异常，设置失败.
	 */
	bool stopDrag();

	/**
	 * 设置工具和负载的质量、质心和惯性矩阵.
	 *
	 * @param[in] 工具和负载的质量.
	 * @param[in] 工具和负载的质心 3个.
	 * @param[in] 工具和负载的惯性矩阵 行优先 9个
	 *
	 * @throw CommandException 控制器返回设置失败.
	 * @throw NetworkException 网络连接异常，设置失败.
	 */
	bool setLoad(double loadMess, const std::vector<double> & loadCenter, const std::vector<double> & loadInertia);

	/**
	 * 设置机器人上电状态.
	 * @param[in] 机器人上电状态，0代表机器人下电，1代表机器人上电
	 */
	bool setMotorPower(int motorState);

	/**
	 * 设置机器人关节软限位
	 * @param[in] upper_joint_limit 软限位最大值，单位:rad
	 * @param[in] lower_joint_limit 软限位最小值, 单位:rad
	 * @param[in] auto_limit 置为true时，机器人在即将到达限位时会对关节角度进行限幅处理，机器人不至于下电
	 *
	 * @throw CommandException 控制器返回设置失败.
	 * @throw NetworkException 网络连接异常，设置失败.
	 */
	bool setJointLimit(const std::vector<double> &upperJointLimit, const std::vector<double> &lowerJointLimit, bool autoLimit);

	/**
	 * 获取机器人上电状态.
	 * @param[in] 机器人上电状态，
	 * @return 0代表机器人下电，1代表机器人上电
	 */
	int getMotorState();

	bool getRobotVersion();
	
	

	

Q_SIGNALS:
	void signalRobotVersion(QString);

protected:

private:
	bool checkMoveCondition();

	/**
	 * 机器人开始运动.
	 * @param[in] 机器人运动速度
	 * @param[in] 机器人运动目标位姿
	 * @return true代表机器人运动完，false代表机器人运动异常
	 */
	bool startMove(double speed, const std::vector<double> &startPose);

	/**
	 * 机器人暂停运动.
	 * @return true代表已暂停，false代表机器人运动异常
	 */
	bool stopMove();

private:
	std::unique_ptr<RobotUtility> robotUtility = {};

	std::atomic<RobotState> currRobotState{ RobotState::ROBOT_NONE };
	std::atomic<RobotErrorCode> currRobotErrorCode{ RobotErrorCode::ROBOT_EXCE_NONE };
};

#endif		//ROBOT_CONTROLLER_H