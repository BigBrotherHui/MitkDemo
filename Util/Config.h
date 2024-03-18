#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <QtCore/QSettings>

class Config {

public:

	static bool init(const QString& filename);
	static void uninit();
	static void save();

	static QString getValue(const QString& key);
	static QStringList getValueList(const QString& key);
	static void setValue(const QString& key, const QString& value);
	static void setValueList(const QString& key, const QStringList& valueList);


	static QString robotIp();
	static void setRobotIp(const QString& ipAddress);
	static int robotPort();
	static void setRobotPort(int port);

	static void SetRunning(bool pRunning);

	static bool GetRunning();
	static bool GetRememberMe();
	/**
	 * @brief 设置是否记录信息信息
	 * @param rememberMe true:记录信息信息
	 */
	static void SetRememberMe(bool rememberMe);
	/**
	 * @brief 获取上次登录名
	 * @return 登录名
	 */
	static QString GetLoginName();

	static void SetLoginName(QString loginName);
	/**
	 * @brief 获取上次密码
	 * @return 密码
	 */
	static QString GetPassword();

	static void SetPassword(QString password);
	/**
	 * @brief 设置上次登录信息
	 * @param loginName 登录名
	 * @param password 密码
	 */
	static void SetLastLogin(QString loginName, QString password);

private:
	//static QSettings* settings;
	static QSettings* settings;
};

#endif /*#ifndef _CONFIG_H_*/

