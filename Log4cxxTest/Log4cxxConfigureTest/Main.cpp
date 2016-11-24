#include <iostream>

#include "LogTool.h"

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool::GetInstance()->Info("Info testing");

	return 0;
}
