#include <iostream>

#include "LogTool.h"

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool* pLog = LogTool::GetInstance();

	pLog->Info("Without LocationInfo --> Info testing");
	pLog->Info(std::string("Without LocationInfo --> Hello"));
	pLog->Info(std::string("With LocationInfo --> Hello"), LOG4CXX_LOCATION);

	char pCharMsg[] = "Const char test";
	pLog->Info("Without LocationInfo --> %s,%d,%f,%d", pCharMsg, 5, 3.5, true);
	pLog->Info(LOG4CXX_LOCATION, "With LocationInfo --> %s,%d,%f,%d", pCharMsg, 5, 3.5, true);

	pLog->Trace(LOG4CXX_LOCATION, "Trace Testing %d", 110);
	pLog->Debug(LOG4CXX_LOCATION, "Debug Testing %d", 11);
	pLog->Info(LOG4CXX_LOCATION, "Info Testing %d", 112);
	pLog->Warn(LOG4CXX_LOCATION, "Warn Testing %d", 113);
	pLog->Error(LOG4CXX_LOCATION, "Error Testing %d", 114);
	pLog->Fatal(LOG4CXX_LOCATION, "Fatal Testing %d", 115);

	return 0;
}
