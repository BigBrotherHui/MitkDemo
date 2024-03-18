#pragma once
#include <RCF/RCF.hpp>
#include <string>
#include <vector>
#include <RCF/Idl.hpp>
#include <SF/vector.hpp>

RCF_BEGIN(RobotRcfService, "RobotRcfService")
RCF_METHOD_R2(bool, startMove, double, const std::vector<double> &)
RCF_METHOD_R0(bool, stopMove)
RCF_METHOD_R0(std::vector<double>, getCurrentRobotPose)
RCF_METHOD_R0(std::vector<double>, getCurrentRobotJoint)
RCF_METHOD_R0(int, getSafetyStopState)
RCF_METHOD_R0(bool, rebootRobot)
RCF_METHOD_R2(bool, startDrag, int, int)
RCF_METHOD_R0(bool, stopDrag)
RCF_METHOD_R3(bool, setLoad, double, const std::vector<double> &, const std::vector<double> &)
RCF_METHOD_R1(bool, setMotorPower, int)
RCF_METHOD_R0(int, getMotorState)
RCF_METHOD_R0(std::vector<int>, getRobotState)
RCF_METHOD_R3(bool, setJointLimit, const std::vector<double> &, const std::vector<double> &, bool)

RCF_END(RobotRcfService)