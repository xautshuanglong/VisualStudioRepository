#include <iostream>

#include "LogTool.h"

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool* pLog = LogTool::GetInstance();

	pLog->Info("Info testing");
	pLog->Info(std::string("Hello"));
	pLog->Info(std::string("Hello"), LOG4CXX_LOCATION);

	char pCharMsg[] = "Const char test";
	pLog->Info("%s,%d,%f,%d", pCharMsg, 5, 3.5, true);
	pLog->Info(LOG4CXX_LOCATION, "%s,%d,%f,%d", pCharMsg, 5, 3.5, true);

	return 0;
}
