#pragma once

#include <mutex>

#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/spi/location/locationinfo.h>

class LogTool
{
public:
	~LogTool();
	static LogTool* GetInstance();

	void Info(char *msg);

private:
	LogTool();
	static LogTool* m_pInstance;
	//static std::mutex m_instanceMutex;
	log4cxx::ConsoleAppenderPtr m_pConsoleAppender;
	log4cxx::PatternLayoutPtr m_pPatternLayout;
	log4cxx::LoggerPtr m_pLogger;
	log4cxx::helpers::Pool m_pool;

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
