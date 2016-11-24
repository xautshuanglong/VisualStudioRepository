#pragma once

#include <mutex>

class LogTool
{
public:
	~LogTool();
	static LogTool* GetInstance();

private:
	LogTool();
	static LogTool* m_pInstance;
	//static std::mutex m_instanceMutex;

	class Helpper
	{
	public:
		Helpper()
		{
			m_pInstance = new LogTool();
		}
		~Helpper()
		{
			//m_instanceMutex.lock();
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
			}
			//m_instanceMutex.unlock();
		}
	};
	static Helpper helpper;
};

