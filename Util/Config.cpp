#include "Config.h"
#include <QDir>
#include <QTextCodec>
#include <QVariantList>

QSettings* Config::settings = nullptr;


const QString CONFIG_ROBOT_IP = "/robot/robotIp";
const QString CONFIG_ROBOT_PORT = "/robot/robotPort";


const QString CONFIG_SYSTEM_RUNNINGSTATE = "/system/runningState";

const QString CONFIG_LOGIN_REMEMBERME = "/login/rememberMe";
const QString CONFIG_LOGIN_NAME = "/login/loginName";
const QString CONFIG_LOGIN_PASSWORD = "/login/password";


//const QString CONFIG_ROBOT_PORT = "/login/robotPort";
//const QString CONFIG_ROBOT_PORT = "/login/robotPort";
//const QString CONFIG_ROBOT_PORT = "/login/robotPort";


bool Config::init(const QString & filename)
{
	Config::uninit();
	settings = new QSettings(filename, QSettings::IniFormat);
	settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
	return true;
}

void Config::uninit()
{
	if (settings != nullptr) {
		settings->sync();
		delete settings;
		settings = nullptr;
	}
}

void Config::save()
{
	if (settings != nullptr) {
		settings->sync();
	}
}

QString Config::getValue(const QString& key)
{
	return settings->value(key, "").toString();
}

QStringList Config::getValueList(const QString& key)
{
	return settings->value(key, "").toStringList();
}

void Config::setValue(const QString& key, const QString& value)
{
	settings->setValue(key, value);
}

void Config::setValueList(const QString& key, const QStringList& valueList)
{
	//QVariantList valueList;
	settings->setValue(key, valueList);
}




QString Config::robotIp()
{
	return settings->value(CONFIG_ROBOT_IP, "127.0.0.1").toString();
}

void Config::setRobotIp(const QString & ipAddress)
{
	settings->setValue(CONFIG_ROBOT_IP, ipAddress);
}

int Config::robotPort()
{
	return settings->value(CONFIG_ROBOT_PORT, 6105).toInt();
}

void Config::setRobotPort(int port)
{
	settings->setValue(CONFIG_ROBOT_PORT, port);
}

void Config::SetRunning(bool pRunning)
{
	
	settings->setValue(CONFIG_SYSTEM_RUNNINGSTATE, pRunning);
}

bool Config::GetRunning()
{
	return settings->value(CONFIG_SYSTEM_RUNNINGSTATE, true).toBool();
}

bool Config::GetRememberMe()
{
	return settings->value(CONFIG_LOGIN_REMEMBERME, false).toBool();
}

void Config::SetRememberMe(bool rememberMe)
{
	settings->setValue(CONFIG_LOGIN_REMEMBERME, rememberMe);
}

QString Config::GetLoginName()
{
	return settings->value(CONFIG_LOGIN_NAME, "sss").toString();
}


void Config::SetLoginName(QString loginName)
{
	settings->value(CONFIG_LOGIN_NAME, loginName);
}

QString Config::GetPassword()
{
	return settings->value(CONFIG_LOGIN_PASSWORD, "sss").toString();
}

void Config::SetPassword(QString password)
{
	settings->value(CONFIG_LOGIN_PASSWORD, password);
}

void Config::SetLastLogin(QString loginName, QString password)
{
	SetLoginName(loginName);
	SetPassword(password);
}

