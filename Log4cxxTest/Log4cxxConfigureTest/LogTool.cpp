#include <iostream>

#include "LogTool.h"

LogTool* LogTool::m_pInstance = nullptr;
LogTool::Helpper LogTool::helpper;
//std::mutex LogTool::m_instanceMutex;

LogTool::LogTool()
{
	//std::cout << "LogTool::LogTool()" << std::endl;
	m_pConsoleAppender = new log4cxx::ConsoleAppender();
	m_pPatternLayout = new log4cxx::PatternLayout();

	m_pPatternLayout->setConversionPattern(log4cxx::LogString(L"%d{yyyy-MM-dd HH:mm:ss.SSS} [%-5p] %C.%M %m (%F:%L)%n"));
	m_pConsoleAppender->setLayout(m_pPatternLayout);
	m_pConsoleAppender->activateOptions(m_pool);

	m_pLogger = log4cxx::Logger::getRootLogger();
	m_pLogger->addAppender(m_pConsoleAppender);
}

LogTool::~LogTool()
{
	std::cout << "LogTool::~LogTool()" << std::endl;
}

LogTool* LogTool::GetInstance()
{
	//if (m_pInstance == nullptr)
	//{
	//	m_instanceMutex.lock();
	//	if (m_pInstance == nullptr)
	//	{
	//		m_pInstance = new LogTool();
	//	}
	//	m_instanceMutex.unlock();
	//}

	return m_pInstance;
}

void LogTool::Info(char *msg)
{
	//std::cout << msg << std::endl;
	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msg, log4cxx::spi::LocationInfo("*", "*", 0));
		//m_pLogger->info(msg);
	}
}
