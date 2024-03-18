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
	 * @brief �����Ƿ��¼��Ϣ��Ϣ
	 * @param rememberMe true:��¼��Ϣ��Ϣ
	 */
	static void SetRememberMe(bool rememberMe);
	/**
	 * @brief ��ȡ�ϴε�¼��
	 * @return ��¼��
	 */
	static QString GetLoginName();

	static void SetLoginName(QString loginName);
	/**
	 * @brief ��ȡ�ϴ�����
	 * @return ����
	 */
	static QString GetPassword();

	static void SetPassword(QString password);
	/**
	 * @brief �����ϴε�¼��Ϣ
	 * @param loginName ��¼��
	 * @param password ����
	 */
	static void SetLastLogin(QString loginName, QString password);

private:
	//static QSettings* settings;
	static QSettings* settings;
};

#endif /*#ifndef _CONFIG_H_*/

