#ifndef LOG_H
#define LOG_H

#include<iostream>
#include <log4cplus/initializer.h>


class Log
{
public:
	static Log* getInstance();
	static void destoryInstance();

	void error(const char* modelName, const char* msg);
	void warn(const char* modelName, const char* msg);
	void info(const char* modelName, const char* msg);
	void debug(const char* modelName, const char* msg);

protected:
	Log(const char *configFile = "../DentalRobot/Logger.properties");

	std::string formatString(/*const Level level, */const char* modelName, const char* msg);
	//std::string getLevelString(const Level level);

private:
	static Log* s_instance;
	log4cplus::Initializer s_initializer;
};

#endif
