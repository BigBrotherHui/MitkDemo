#ifndef SYSTEM_CONTROLER_H
#define SYSTEM_CONTROLER_H

// QT
#include <QtCore/QObject>


// STL
#include <string.h>

// RCF
//#include <RCF/RCF.hpp>


#include "RobotController.h"
#include "RobotCommThread.h"

class SystemControler : public QObject
{
	Q_OBJECT

public:
	static SystemControler* getInstance();
	RobotController* getRobotControler() { return robotControler; }

	SystemControler(const SystemControler&) = delete;
	SystemControler& operator=(const SystemControler&) = delete;


	void startThreads();
	void stopThreads();
	void init();
	void destory();

private:

	static SystemControler* thisControler;
 	RobotCommThread* robotCommThread = nullptr;
 	RobotController* robotControler = nullptr;

private:
	SystemControler();
	~SystemControler();
};
#endif // SYSTEM_CONTROLER_H