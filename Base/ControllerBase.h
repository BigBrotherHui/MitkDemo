#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <QtCore/QObject>


class ControllerBase : public QObject
{
	Q_OBJECT

public:
	explicit ControllerBase(QObject *parent = nullptr);
	virtual ~ControllerBase();

	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void destroy() = 0;
	virtual bool hasHeartBeat() = 0;
	virtual bool isException() = 0;

Q_SIGNALS:
	//void signalShowError(QString);

//public Q_SLOTS:
};

#endif		//CONTROLLER_BASE_H