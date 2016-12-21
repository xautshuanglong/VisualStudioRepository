#include <iostream>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/BasicConfigurator.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/LayoutAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

using namespace std;

int main()
{
	log4cpp::BasicConfigurator::configure();

	// Every appender have a mutual independent layout.
	log4cpp::PatternLayout* consoleLayout = new log4cpp::PatternLayout();
	log4cpp::PatternLayout* fileLayout = new log4cpp::PatternLayout();
	log4cpp::PatternLayout* rollLayout = new log4cpp::PatternLayout();
	consoleLayout->setConversionPattern("%d{%H:%M:%S.%l} [%-5p] [%t] %c %m%n");
	fileLayout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S.%l} [%-5p] [%t] %c %m%n");
	rollLayout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S.%l} [%-5p] [%t] %c %m%n");
	
	// default appender, is equivalent to ostreamAppender with std::cout.
	log4cpp::Category& root = log4cpp::Category::getRoot();
	root.getAppender()->setLayout(consoleLayout);

	// FileAppender testing.
	log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("fileAppender", ".//TempDebug.log",false);
	fileAppender->setLayout(fileLayout);
	root.addAppender(fileAppender);

	// RollingFileAppender testing.
	log4cpp::RollingFileAppender* rollingApender = new log4cpp::RollingFileAppender("rollingAppender", ".//RollingFile.log",1024*1024,10);
	rollingApender->setLayout(rollLayout);
	root.addAppender(rollingApender);

	log4cpp::Category& cat = root.getInstance("Log4cppTest");

	cat.setPriority(log4cpp::Priority::DEBUG);
	cat.info("info Testing");
	cat.debug("debug Testing");
	cat.error("error Testing");
	cat.fatal("fatal Testing");
	cat.warn("warn Testing");
	cat.emerg("emerg Testing");// 优先级 等同于 fatal

	log4cpp::Category::shutdown();

	return 0;
}