#pragma once

#include <mutex>

#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>
#include <log4cxx/filter/levelrangefilter.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/rollingfileappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/spi/appenderattachable.h>
#include <log4cxx/spi/location/locationinfo.h>

#define MAX_FILENAME_LENGTH 1024 // 日志相关路径长度
#define MAX_MSG_BUFFER_LEN  1024 // 日志文件长度

#define VA_ARGUMENTS_SPRINT(fmt,msgBuffer,length) \
va_list argList; \
va_start(argList, fmt); \
vsnprintf(msgBuffer, length, fmt, argList); \
va_end(argList); 

#ifdef _UNICODE
#define SL_TSTRING std::wstring
#define	SL_ACCESS _waccess
#define SL_MAKEDIR _wmkdir
#else
#define SL_TSTRING std::string
#define	SL_ACCESS _access
#define SL_MAKEDIR _mkdir
#endif

volatile class LogTool
{
public:
	static LogTool* GetInstance();

	void Trace(const char *fmat, ...);
	void Trace(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Trace(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

	void Debug(const char *fmat, ...);
	void Debug(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Debug(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

	void Info(const char *fmat, ...);
	void Info(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Info(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

	void Warn(const char *fmat, ...);
	void Warn(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Warn(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

	void Error(const char *fmat, ...);
	void Error(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Error(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

	void Fatal(const char *fmat, ...);
	void Fatal(log4cxx::spi::LocationInfo location, const char *fmat, ...);
	void Fatal(std::string& msg, log4cxx::spi::LocationInfo& location = log4cxx::spi::LocationInfo("", "", 0));

private:
	LogTool();
	~LogTool();
	static LogTool* volatile m_pInstance;

	static std::mutex m_instanceMutex;
	log4cxx::ConsoleAppenderPtr				m_pConsoleAppender;		// 输出到控制台
	log4cxx::FileAppenderPtr				m_pFileAppender;		// 输出到临时 TempFile.log
	log4cxx::RollingFileAppenderPtr			m_pRollingFileAppender;	// 输出到回滚文件 RollingFile.log
	log4cxx::helpers::Pool					m_pool;
	log4cxx::LoggerPtr m_pLogger;

	std::string m_strFileName, m_strMethodName;// 函数定位信息：调整源文件名及函数名长度

	SL_TSTRING m_strLogDir;
	SL_TSTRING m_strCurExeDir;

	void CreateLogDirectory();
	void BasicConfiguration();
	void ChangeAppenderFilter();
	log4cxx::spi::LocationInfo GetShortName(log4cxx::spi::LocationInfo location);

	class Helpper
	{
	public:
		Helpper()
		{
			//m_pInstance = new LogTool();
		}
		~Helpper()
		{
			m_instanceMutex.lock();
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
			}
			m_instanceMutex.unlock();
		}
	};
	static Helpper helpper;
};
