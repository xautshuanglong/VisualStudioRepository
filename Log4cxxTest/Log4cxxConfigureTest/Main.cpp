#include <iostream>

#include "LogTool.h"

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool::GetInstance()->Info("Info testing");
	LogTool::GetInstance()->Info(std::string("Hello"));
	LogTool::GetInstance()->Info(std::string("Hello"), LOG4CXX_LOCATION);

	char pCharMsg[] = "Const char test";
	LogTool::GetInstance()->Info("%s,%d,%f,%d", pCharMsg, 5, 3.5, true);
	LogTool::GetInstance()->Info(LOG4CXX_LOCATION, "%s,%d,%f,%d", pCharMsg, 5, 3.5, true);

	return 0;
}
