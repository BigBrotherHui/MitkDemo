#undef UNICODE

#include "Log.h"

#include <stdarg.h>
#include <cstdlib>
#include <iostream>
#include <log4cplus/config.hxx>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/spi/loggerimpl.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/loggingmacros.h>

Log* Log::s_instance = nullptr;
Log::Log(const char *configFile)
{
	try {

		log4cplus::BasicConfigurator config;
		config.configure();
		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
		log4cplus::PropertyConfigurator::doConfigure(configFile);
	}
	catch (...) {
		std::cout << "************************" << std::endl;
		std::cout << "Logger init is failed." << std::endl;
		std::cout << "************************" << std::endl;
		throw;
	}

	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "*****************************");
	LOG4CPLUS_INFO(_logger, "Logger System Start......");
	LOG4CPLUS_INFO(_logger, "*****************************");
}

Log* Log::getInstance()
{
	if (s_instance == nullptr)	{
		s_instance = new Log();
	}
	return s_instance;
}

void Log::destoryInstance()
{
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "*****************************");
	LOG4CPLUS_INFO(_logger, "Logger System Stop......");
	LOG4CPLUS_INFO(_logger, "*****************************");

	_logger.shutdown();
	log4cplus::deinitialize();

	if (s_instance != nullptr) {
		delete s_instance;
		s_instance = nullptr;
	}
	return;
}

#define DO_LOGGER(logLevel, msg)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
    if(_logger.isEnabledFor(logLevel))\
	{\
		_logger.forcedLog(logLevel, msg); \
	}

void Log::error(const char* modelName, const char* msg)
{
	DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, formatString(modelName, msg));
}

void Log::warn(const char* modelName, const char* msg)
{
	DO_LOGGER(log4cplus::WARN_LOG_LEVEL, formatString(modelName, msg));
}

void Log::info(const char* modelName, const char* msg)
{
	DO_LOGGER(log4cplus::INFO_LOG_LEVEL, formatString(modelName, msg));
}

void Log::debug(const char* modelName, const char* msg)
{
	DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, formatString(modelName, msg));
}

std::string Log::formatString(const char* modelName, const char* msg)
{
	//std::string levelString = getLevelString(level);
	std::ostringstream stringStream;
	stringStream /*<< levelString << ", " */ << modelName << " : " << msg;
	std::string copyOfStr = stringStream.str();

	return copyOfStr;
}
