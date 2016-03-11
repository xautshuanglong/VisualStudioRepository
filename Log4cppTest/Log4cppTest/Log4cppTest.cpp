#include <iostream>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/BasicConfigurator.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>

using namespace std;

int main()
{
	cout << "Log4cppTest" << endl;
	log4cpp::BasicConfigurator::configure();
	log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
	log4cpp::Category::getRoot().getAppender()->setLayout(layout);
	log4cpp::Category& cat = log4cpp::Category::getInstance("cat1");

	layout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S.%l} [%-5p] %c %m%n");
	cat.setPriority(log4cpp::Priority::DEBUG);
	cat.info("ha ha");
	cat.debug("debug Testing");
	cat.error("error Testing");
	cat.fatal("fatal Testing");
	cat.warn(string("warn Testing"));

	log4cpp::Category::shutdown();

	return 0;
}