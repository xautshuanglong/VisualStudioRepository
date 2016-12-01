#include <windows.h>
#include <iostream>
#include <io.h>
#include <direct.h>

#include "LogTool.h"

LogTool* volatile LogTool::m_pInstance = nullptr;
LogTool::Helpper LogTool::helpper;
std::mutex LogTool::m_instanceMutex;

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

	CreateLogDirectory();
}

LogTool::~LogTool()
{
	//std::cout << "LogTool::~LogTool()" << std::endl;
}

LogTool* LogTool::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_instanceMutex.lock();
		if (m_pInstance == nullptr)
		{
			m_pInstance = new LogTool();
		}
		m_instanceMutex.unlock();
	}

	return m_pInstance;
}

void LogTool::CreateLogDirectory()
{
	std::string strExeDir = "\\logs";
	char curExeDir[MAX_FILENAME_LENGTH] = { 0 };
	if (GetModuleFileName(nullptr, curExeDir, MAX_FILENAME_LENGTH) != 0)
	{
		strExeDir = curExeDir;
		size_t index = strExeDir.find_last_of("\\");
		strExeDir = strExeDir.substr(0, index) + "\\logs";
		std::cout << strExeDir << std::endl;
	}

	if (_access(strExeDir.c_str(), 0) == -1)
	{
		int ret = _mkdir(strExeDir.c_str());
		std::cout << "ret = " << ret << std::endl;
	}
}

void LogTool::Info(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN);
	
	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, location);
	}
}

void LogTool::Info(const char *fmt, ...)
{
	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, log4cxx::spi::LocationInfo("*", "*", 0));
	}
}

void LogTool::Info(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msg, location);
	}
}
