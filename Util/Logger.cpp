#include "Logger.h"
#include "Log.h"
//#include <iostream>

void Logger::destoryLogger()
{
	Log::destoryInstance();
}

bool Logger::writeErrorLog(const char* modelName, const char* msg)
{
	try {
		Log::getInstance()->error(modelName, msg);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool Logger::writeWarnLog(const char* modelName, const char* msg)
{
	try {
		Log::getInstance()->warn(modelName, msg);
	}
	catch (...)	{
		return false;
	}
	return true;
}

bool Logger::writeInfoLog(const char* modelName, const char* msg)
{
	try {
		Log::getInstance()->info(modelName, msg);
	}
	catch (...)	{
		return false;
	}
	return true;
}

bool Logger::writeDebugLog(const char* modelName, const char* msg)
{
	try {
		Log::getInstance()->debug(modelName, msg);
	}
	catch (...)	{
		return false;
	}
	return true;
}
