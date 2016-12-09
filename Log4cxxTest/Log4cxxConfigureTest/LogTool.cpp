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
	
	if (SL_ACCESS((m_strCurExeDir+TEXT("\\config\\log4cxx.properties")).c_str(), 0) != -1)
	{
		log4cxx::PropertyConfigurator::configureAndWatch(m_strCurExeDir + TEXT("\\config\\log4cxx.properties"));
	}
	else
	{
		BasicConfiguration();
	}
	m_pLogger = log4cxx::Logger::getRootLogger();
	ChangeAppenderFilter();
}

LogTool::~LogTool()
{
	//std::cout << "LogTool::~LogTool()" << std::endl;
	log4cxx::LogManager::shutdown();
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
	SL_TSTRING strLogDir = TEXT("logs");
	TCHAR curExeDir[MAX_FILENAME_LENGTH] = { 0 };
	if (GetModuleFileName(nullptr, curExeDir, MAX_FILENAME_LENGTH) != 0)
	{
		strLogDir = curExeDir;
		size_t index = strLogDir.find_last_of(TEXT("\\"));
		m_strCurExeDir = strLogDir.erase(index);
		strLogDir.append(TEXT("\\logs"));
	}

	if (SL_ACCESS(strLogDir.c_str(), 0) == -1)
	{
		int ret = SL_MAKEDIR(strLogDir.c_str());
		//std::cout << "ret = " << ret << std::endl;
	}
	m_strLogDir = strLogDir;// 设置日志文件夹绝对路径【当前文件夹下的 logs 文件夹】
}

void LogTool::BasicConfiguration()
{
	log4cxx::PatternLayoutPtr				pTempFileLayout;		// 临时文件和控制台日志布局
	log4cxx::PatternLayoutPtr				pRollingFileLayout;		// 回滚文件日志布局

	m_pConsoleAppender = new log4cxx::ConsoleAppender();
	pTempFileLayout = new log4cxx::PatternLayout();
	pRollingFileLayout = new log4cxx::PatternLayout();
	m_pFileAppender = new log4cxx::FileAppender();
	m_pRollingFileAppender = new log4cxx::RollingFileAppender();

	// 输出日志到控制台
	pTempFileLayout->setConversionPattern(log4cxx::LogString(TEXT("%d{HH:mm:ss.SSS} [%-5p] %m    <- %C::%M (%F:%L)%n")));
	m_pConsoleAppender->setLayout(pTempFileLayout);
	//m_pConsoleAppender->addFilter();

	// 输出日志到临时调试文件（不追加，只记录一次运行结果）
	m_pFileAppender->setLayout(pTempFileLayout);
	m_pFileAppender->setFile(m_strLogDir + LOG4CXX_STR("\\TempFile.log"));
	m_pFileAppender->setAppend(false);

	// 输出日志到回滚文件（用于长期记录）
	pRollingFileLayout->setConversionPattern(log4cxx::LogString(TEXT("%d{yyyy-MM-dd HH:mm:ss.SSS} [%-5p] %m    <- %C::%M (%F:%L)%n")));
	m_pRollingFileAppender->setLayout(pRollingFileLayout);
	//m_pRollingFileAppender->setAppend(true); // default mode is true;
	m_pRollingFileAppender->setMaxBackupIndex(10);
	m_pRollingFileAppender->setMaxFileSize(LOG4CXX_STR("10MB"));

	m_pConsoleAppender->activateOptions(m_pool);
	m_pFileAppender->activateOptions(m_pool);
	m_pRollingFileAppender->activateOptions(m_pool);

	log4cxx::Logger::getRootLogger()->addAppender(m_pConsoleAppender);// 控制台输出日志耗时
	log4cxx::Logger::getRootLogger()->addAppender(m_pFileAppender);
	log4cxx::Logger::getRootLogger()->addAppender(m_pRollingFileAppender);
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
		if (allAppenders[i]->instanceof(log4cxx::ConsoleAppender::getStaticClass()))
		{
			continue;
			//std::cout << "ConsoleAppender" << std::endl;
		}
		else if (allAppenders[i]->instanceof(log4cxx::RollingFileAppender::getStaticClass()))
		{
			log4cxx::RollingFileAppenderPtr tempRollingAppender = allAppenders[i];
			tempRollingAppender->setFile(m_strLogDir + LOG4CXX_STR("\\RollingFile.log"));
			tempRollingAppender->activateOptions(m_pool);
			continue;
			//std::cout << "RollingFileAppender" << std::endl;
		}
		else if (allAppenders[i]->instanceof(log4cxx::FileAppender::getStaticClass()))
		{
#ifdef _DEBUG
			log4cxx::FileAppenderPtr tempFileAppender = allAppenders[i];
			tempFileAppender->setFile(m_strLogDir + LOG4CXX_STR("\\TempFile.log"));
			tempFileAppender->activateOptions(m_pool);
#else
			allAppenders[i]->clearFilters();
			log4cxx::Logger::getRootLogger()->removeAppender(allAppenders[i]);
#endif
			continue;
			//std::cout << "FileAppender" << std::endl;
		}
		else
		{
			allAppenders[i]->clearFilters();
			log4cxx::Logger::getRootLogger()->removeAppender(allAppenders[i]);
		}
	}
}

log4cxx::spi::LocationInfo LogTool::GetShortName(log4cxx::spi::LocationInfo location)
{
	std::string strClassName = location.getClassName();// 暂存类名
	m_strFileName = location.getFileName();// 暂存文件名
	m_strMethodName = location.getMethodName();// 暂存方法名

	// 缩短文件名
	size_t index = m_strFileName.find_last_of('\\');
	if (index != std::string::npos)
	{
		m_strFileName.erase(0, index + 1);
	}

	// 缩短方法名
	index = m_strMethodName.find_last_of(' ');
	if (index != std::string::npos)
	{
		m_strMethodName.erase(0, index + 1);
	}

	// 加入类名
	if (strClassName.length() > 0)
	{
		strClassName.append("::");
		m_strMethodName.insert(0, strClassName);
	}

	return log4cxx::spi::LocationInfo(m_strFileName.c_str(), m_strMethodName.c_str(), location.getLineNumber());
}

void LogTool::Trace(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isTraceEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->trace(msgBuffer, GetShortName(location));
	}
}

void LogTool::Trace(const char *fmt, ...)
{
	if (m_pLogger->isTraceEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->trace(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Trace(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isTraceEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->trace(msg, GetShortName(location));
	}
}

void LogTool::Debug(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isDebugEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->debug(msgBuffer, GetShortName(location));
	}
}

void LogTool::Debug(const char *fmt, ...)
{
	if (m_pLogger->isDebugEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->debug(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Debug(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isDebugEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->debug(msg, GetShortName(location));
	}
}

void LogTool::Info(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);
	
	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, GetShortName(location));
	}
}

void LogTool::Info(const char *fmt, ...)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Info(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isInfoEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->info(msg, GetShortName(location));
	}
}

void LogTool::Warn(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isWarnEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->warn(msgBuffer, GetShortName(location));
	}
}

void LogTool::Warn(const char *fmt, ...)
{
	if (m_pLogger->isWarnEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->warn(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Warn(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isWarnEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->warn(msg, GetShortName(location));
	}
}

void LogTool::Error(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isErrorEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->error(msgBuffer, GetShortName(location));
	}
}

void LogTool::Error(const char *fmt, ...)
{
	if (m_pLogger->isErrorEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->error(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Error(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isErrorEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->error(msg, GetShortName(location));
	}
}

void LogTool::Fatal(log4cxx::spi::LocationInfo location, const char *fmt, ...)
{
	if (m_pLogger->isFatalEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->fatal(msgBuffer, GetShortName(location));
	}
}

void LogTool::Fatal(const char *fmt, ...)
{
	if (m_pLogger->isFatalEnabled() == false) return;

	char msgBuffer[MAX_MSG_BUFFER_LEN];
	VA_ARGUMENTS_SPRINT(fmt, msgBuffer, MAX_MSG_BUFFER_LEN - 1);

	if (m_pLogger != nullptr)
	{
		m_pLogger->fatal(msgBuffer, log4cxx::spi::LocationInfo("", "", 0));
	}
}

void LogTool::Fatal(std::string& msg, log4cxx::spi::LocationInfo& location/* =log4cxx::spi::LocationInfo("*","*",0) */)
{
	if (m_pLogger->isFatalEnabled() == false) return;

	if (m_pLogger != nullptr)
	{
		m_pLogger->fatal(msg, GetShortName(location));
	}
}
