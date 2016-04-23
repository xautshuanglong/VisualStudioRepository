#ifndef _LOGTOOL_H
#define _LOGTOOL_H

#include <log4cpp/Category.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PropertyConfigurator.hh>

using namespace log4cpp;

class LogTool
{

private:
	LogTool();// 私有构造，禁止外部实例化
	static LogTool* m_pInstance;
public:
	//static const LogTool* getInstance();
	static LogTool* getInstance();
	void info(const char* msg);
	void info(std::string& msg);
	void debug(const char* msg);
	void debug(std::string& msg);
	void error(const char* msg);
	void error(std::string& msg);
	void pushNDC(const std::string& msg);
	void popNDC();
};

#endif // !_LOGTOOL_H