#pragma once

#include <mutex>

#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/spi/location/locationinfo.h>

#define MAX_FILENAME_LENGTH 1024
#define MAX_MSG_BUFFER_LEN  1024

#define VA_ARGUMENTS_SPRINT(fmt,msgBuffer,length) \
va_list argList; \
va_start(argList, fmt); \
vsnprintf(msgBuffer, length, fmt, argList); \
va_end(argList); 

class LogTool
{
public:
	~LogTool();
	static LogTool* GetInstance();

	void Info(const char *fmat, ...);
	void Info(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Info(std::string& msg, log4cxx::spi::LocationInfo& location=log4cxx::spi::LocationInfo("*","*",0));

private:
	LogTool();
	static LogTool* m_pInstance;

	//static std::mutex m_instanceMutex;
	log4cxx::ConsoleAppenderPtr m_pConsoleAppender;
	log4cxx::PatternLayoutPtr m_pPatternLayout;
	log4cxx::LoggerPtr m_pLogger;
	log4cxx::helpers::Pool m_pool;

	void CreateLogDirectory();

	class Helpper
	{
	public:
		Helpper()
		{
			m_pInstance = new LogTool();
		}
		~Helpper()
		{
			//m_instanceMutex.lock();
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
			}
			//m_instanceMutex.unlock();
		}
	};
	static Helpper helpper;
};
