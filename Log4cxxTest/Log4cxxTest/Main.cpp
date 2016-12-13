#include <iostream>
#include <windows.h>

#include <log4cxx/logger.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/simplelayout.h>

void ConfigureByCode();

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Test ==========================" << std::endl;
	ConfigureByCode();

	log4cxx::Logger::getRootLogger()->debug("Debug Testing...");
	log4cxx::Logger::getRootLogger()->info("Info Testing...");
	log4cxx::LoggerPtr log = log4cxx::Logger::getRootLogger();
	LOG4CXX_DEBUG(log, "Debug Test");
	log->debug(__FUNCSIG__);
	log->debug("function name testing ", LOG4CXX_LOCATION);
	log->info(std::string("std::string::format"), LOG4CXX_LOCATION);

	log4cxx::LogManager::shutdown();
	
	return 0;
}

void ConfigureByCode()
{
	log4cxx::ConsoleAppenderPtr consoleAppender(new log4cxx::ConsoleAppender());
	//log4cxx::SimpleLayoutPtr simpleLayout(new log4cxx::SimpleLayout());
	log4cxx::PatternLayoutPtr patternLayout(new log4cxx::PatternLayout());
	log4cxx::helpers::Pool pool;

	patternLayout->setConversionPattern(log4cxx::LogString(TEXT("%d{yyyy-MM-dd HH:mm:ss.SSS} [%-5p] %C.%M %m (%F:%L)%n")));

	consoleAppender->setLayout(patternLayout);
	consoleAppender->activateOptions(pool);
	log4cxx::Logger::getRootLogger()->addAppender(consoleAppender);
}