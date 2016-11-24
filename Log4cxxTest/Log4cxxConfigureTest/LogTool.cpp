#include <iostream>

#include "LogTool.h"

LogTool* LogTool::m_pInstance = nullptr;
LogTool::Helpper LogTool::helpper;
//std::mutex LogTool::m_instanceMutex;

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
	//if (m_pInstance == nullptr)
	//{
	//	m_instanceMutex.lock();
	//	if (m_pInstance == nullptr)
	//	{
	//		m_pInstance = new LogTool();
	//	}
	//	m_instanceMutex.unlock();
	//}

	return m_pInstance;
}
