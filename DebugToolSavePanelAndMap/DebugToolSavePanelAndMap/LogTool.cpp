#include <iostream>
#include "LogTool.h"

LogTool::LogTool()
{
	try
	{
		PropertyConfigurator::configure("..//config//log4cpp.ini");
	}
	catch (ConfigureFailure& e)
	{
	}
}

LogTool* LogTool::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new LogTool();
	}
	return m_pInstance;
}

void LogTool::info(const char* msg)
{
	//Category& root = Category::getRoot();
	Category& m_fileCategory = Category::getInstance("tempfile");
	Category& m_rollingCategory = Category::getInstance("rolling");
	//root.info(msg);
	m_fileCategory.info(msg);
	m_rollingCategory.info(msg);
}

void LogTool::info(std::string& msg)
{
	//Category& root = Category::getRoot();
	Category& m_fileCategory = Category::getInstance("tempfile");
	Category& m_rollingCategory = Category::getInstance("rolling");
	//root.info(msg);
	m_fileCategory.info(msg);
	m_rollingCategory.info(msg);
}

void LogTool::debug(const char* msg)
{
	//Category::getRoot().debug(msg);
	Category::getInstance("tempfile").debug(msg);
	Category::getInstance("rolling").debug(msg);
}

void LogTool::debug(std::string& msg)
{
	//Category::getRoot().debug(msg);
	Category::getInstance("tempfile").debug(msg);
	Category::getInstance("rolling").debug(msg);
}

void LogTool::error(const char* msg)
{
	//Category::getRoot().error(msg);
	Category::getInstance("tempfile").error(msg);
	Category::getInstance("rolling").error(msg);
}

void LogTool::error(std::string& msg)
{
	//Category::getRoot().error(msg);
	Category::getInstance("tempfile").error(msg);
	Category::getInstance("rolling").error(msg);
}

void LogTool::pushNDC(const std::string& msg)
{
	NDC::push(msg);
}

void LogTool::popNDC()
{
	NDC::pop();
}