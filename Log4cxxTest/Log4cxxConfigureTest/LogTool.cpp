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
	CreateLogDirectory();
	BasicConfigration();
	ChangeAppenderFilter();
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
	SL_TSTRING strExeDir = TEXT("\\logs");
	TCHAR curExeDir[MAX_FILENAME_LENGTH] = { 0 };
	if (GetModuleFileName(nullptr, curExeDir, MAX_FILENAME_LENGTH) != 0)
	{
		strExeDir = curExeDir;
		size_t index = strExeDir.find_last_of(TEXT("\\"));
		strExeDir = strExeDir.substr(0, index) + TEXT("\\logs");
		//std::wcout << strExeDir << std::endl;
	}

	if (SL_ACCESS(strExeDir.c_str(), 0) == -1)
	{
		int ret = SL_MAKEDIR(strExeDir.c_str());
		//std::cout << "ret = " << ret << std::endl;
	}
	m_strLogDir = strExeDir;// 设置日志文件夹绝对路径【当前文件夹下的 logs 文件夹】
}

void LogTool::BasicConfigration()
{
	log4cxx::PatternLayoutPtr				pTempFileLayout;		// 临时文件和控制台日志布局
	log4cxx::PatternLayoutPtr				pRollingFileLayout;		// 回滚文件日志布局

	m_pConsoleAppender = new log4cxx::ConsoleAppender();
	pTempFileLayout = new log4cxx::PatternLayout();
	pRollingFileLayout = new log4cxx::PatternLayout();
	m_pFileAppender = new log4cxx::FileAppender();
	m_pRollingFileAppender = new log4cxx::RollingFileAppender();

	// 输出日志到控制台
	pTempFileLayout->setConversionPattern(log4cxx::LogString(TEXT("%d{HH:mm:ss.SSS} [%-5p] %M %m (%F:%L)%n")));
	m_pConsoleAppender->setLayout(pTempFileLayout);
	//m_pConsoleAppender->addFilter();

	// 输出日志到临时调试文件（不追加，只记录一次运行结果）
	m_pFileAppender->setLayout(pTempFileLayout);
	m_pFileAppender->setFile(m_strLogDir + LOG4CXX_STR("\\TempFile.log"));
	m_pFileAppender->setAppend(false);

	// 输出日志到回滚文件（用于长期记录）
	pRollingFileLayout->setConversionPattern(log4cxx::LogString(TEXT("%d{yyyy-MM-dd HH:mm:ss.SSS} [%-5p] %M %m (%F:%L)%n")));
	m_pRollingFileAppender->setLayout(pRollingFileLayout);
	m_pRollingFileAppender->setFile(m_strLogDir + LOG4CXX_STR("\\RollingFile.log"));
	//m_pRollingFileAppender->setAppend(true); // default mode is true;
	m_pRollingFileAppender->setMaxBackupIndex(10);
	m_pRollingFileAppender->setMaxFileSize(LOG4CXX_STR("10MB"));

	m_pConsoleAppender->activateOptions(m_pool);
	m_pFileAppender->activateOptions(m_pool);
	m_pRollingFileAppender->activateOptions(m_pool);

	m_pLogger = log4cxx::Logger::getRootLogger();
	m_pLogger->addAppender(m_pConsoleAppender);// 控制台输出日志耗时
	m_pLogger->addAppender(m_pFileAppender);
	m_pLogger->addAppender(m_pRollingFileAppender);
}

void LogTool::ChangeAppenderFilter()
{
	log4cxx::filter::LevelRangeFilterPtr	pLevelRangeFilter;		// 对日志等级范围进行过滤
	pLevelRangeFilter = new log4cxx::filter::LevelRangeFilter();
#if _DEBUG
	pLevelRangeFilter->setLevelMin(log4cxx::Level::getDebug());
#else
	pLevelRangeFilter->setLevelMin(log4cxx::Level::getInfo());
#endif
	pLevelRangeFilter->setLevelMax(log4cxx::Level::getFatal());

	log4cxx::AppenderList allAppenders = m_pLogger->getAllAppenders();
	int appenderLen = allAppenders.size();
	for (int i=0; i<appenderLen; i++)
	{
		allAppenders[i]->addFilter(pLevelRangeFilter);
		if (allAppenders[i]->instanceof(m_pConsoleAppender->getClass()))
		{
			continue;
			//std::cout << "ConsoleAppender" << std::endl;
		}
		else if (allAppenders[i]->instanceof(m_pRollingFileAppender->getClass()))
		{
			continue;
			//std::cout << "RollingFileAppender" << std::endl;
		}
		else if (allAppenders[i]->instanceof(m_pFileAppender->getClass()))
		{
			continue;
			//std::cout << "FileAppender" << std::endl;
		}
		else
		{
			allAppenders[i]->clearFilters();
			m_pLogger->removeAppender(allAppenders[i]);
		}
	}
}

log4cxx::spi::LocationInfo LogTool::GetShortName(log4cxx::spi::LocationInfo originLocal)
{
	std::string strFileName(originLocal.getFileName());
	size_t index = strFileName.find_last_of('\\');
	if (index != std::string::npos)
	{
		strFileName.erase(0, index + 1);
	}

	//std::string strMethodName = originLocal.getMethodName();
	//index = strMethodName.find_last_of(' ');
	//if (index != std::string::npos)
	//{
	//	strMethodName = strMethodName.substr(index + 1);
	//}

	log4cxx::spi::LocationInfo newLocation(strFileName.c_str(), originLocal.getMethodName().c_str(), originLocal.getLineNumber());
	std::cout << "newLocation: " << newLocation.getFileName() << "  " << newLocation.getMethodName() << std::endl;

	//return log4cxx::spi::LocationInfo("haha", "hehe", 110);
	return newLocation;
}

void LogTool::Info(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN);
	
	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, location);
	}
}

void LogTool::Info(const char *fmt, ...)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, log4cxx::spi::LocationInfo("*", "*", 0));
	}
}

void LogTool::Info(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		
		m_pLogger->info(msg, location);
	}
}
