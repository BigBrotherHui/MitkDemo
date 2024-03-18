#ifndef LOGGER_H
#define LOGGER_H

class Logger
{
public:
	static void destoryLogger();

	static bool writeErrorLog(const char* modelName, const char* msg);
	static bool writeWarnLog(const char* modelName, const char* msg);
	static bool writeInfoLog(const char* modelName, const char* msg);
	static bool writeDebugLog(const char* modelName, const char* msg);
};

#endif
