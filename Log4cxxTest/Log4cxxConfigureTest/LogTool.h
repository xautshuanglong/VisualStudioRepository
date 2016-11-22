#pragma once
class LogTool
{
public:
	~LogTool();
	static LogTool* GetInstance();

private:
	LogTool();
	static LogTool* m_pInstance;

	class Helpper
	{
	public:
		Helpper() 
		{
			m_pInstance = new LogTool();
		}
		~Helpper()
		{
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
			}
		}
	};
	static Helpper helpper;
};

