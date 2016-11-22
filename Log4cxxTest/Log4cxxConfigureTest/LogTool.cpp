#include <iostream>

#include "LogTool.h"

LogTool* LogTool::m_pInstance = nullptr;
LogTool::Helpper LogTool::helpper;

LogTool::LogTool()
{
	std::cout << "LogTool::LogTool()" << std::endl;
}


LogTool::~LogTool()
{
	std::cout << "LogTool::~LogTool()" << std::endl;
}

LogTool* LogTool::GetInstance()
{
	return m_pInstance;
}
