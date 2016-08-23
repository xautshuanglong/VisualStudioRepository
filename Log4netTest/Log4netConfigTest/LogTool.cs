using log4net;
using log4net.Appender;
using log4net.Config;
using log4net.Core;
using log4net.Filter;
using log4net.Repository.Hierarchy;
using System;
using System.Diagnostics;
using System.IO;

/************************************************************************/
/*        OFF -> FATAL -> ERROR -> WARN -> INFO -> DEBUG -> ALL         */
/************************************************************************/

namespace Log4netConfigTest
{
	public sealed class LogTool
	{
		private static volatile LogTool logInstance = null;
		private static readonly object SynObj = new object();

		private static bool watchFlag = true;
		private static string configFile = "..\\..\\Log4netConfig.xml";
        private static string logFilesDir = ".\\logs";

		private ILog m_log = null;

		private LogTool()
		{
		}

		public static LogTool Instance()
		{
			if (null == logInstance)
			{
				lock (SynObj)
				{
					if (null == logInstance)
					{
						logInstance = new LogTool();
                        logInstance.CheckLogDirectory();
                        if (watchFlag)
                        {
                            XmlConfigurator.ConfigureAndWatch(new FileInfo(configFile));
                        } 
                        else
                        {
                            XmlConfigurator.Configure(new FileInfo(configFile));
                        }
                        logInstance.m_log = LogManager.GetLogger("root");
                        logInstance.ChangeFilterForRelease();
                    }
                }
			}
			return logInstance;
		}

        private void ChangeFilterForRelease()
        {
            IAppender[] appenders = logInstance.m_log.Logger.Repository.GetAppenders();

            LevelRangeFilter levelRange = new LevelRangeFilter();
            levelRange.LevelMin = Level.Info;
            levelRange.LevelMax = Level.Fatal;

            foreach (IAppender appenderItem in appenders)
            {
                if (appenderItem is ConsoleAppender)
                {
                    ConsoleAppender tempAppender = (ConsoleAppender)appenderItem;
#if !DEBUG
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
#endif
                }
                else if (appenderItem is RollingFileAppender)// RollingFileAppender is extends FileAppender,so it should be judged before FileAppender.
                {
                    RollingFileAppender tempAppender = (RollingFileAppender)appenderItem;
#if !DEBUG
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
#endif
                    tempAppender.File = logFilesDir + "\\RollingFile.log";
                }
                else if (appenderItem is FileAppender)
                {
                    FileAppender tempAppender = (FileAppender)appenderItem;
#if !DEBUG
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
#endif
                    tempAppender.File = logFilesDir + "\\TempFile.log";
                }
                else
                {
                    // For security, remove all other appenders.
                    Logger logger = (Logger)m_log.Logger;
                    logger.Parent.RemoveAppender(appenderItem);
                }
            }
        }

        private void CheckLogDirectory()
        {
            string curExeFilename = Process.GetCurrentProcess().MainModule.FileName;
            string curExeDir = curExeFilename.Substring(0, curExeFilename.LastIndexOf("\\"));
            string logsDir = curExeDir + "\\logs";
            logFilesDir = logsDir;// save path to place log files.
#if !DEBUG
            configFile = curExeDir + "\\Log4netConfig.xml";
#else
            configFile = curExeDir + "\\" + configFile;
#endif

            try
            {
                if (!Directory.Exists(logsDir))
                {
                    Directory.CreateDirectory(logsDir);
                }
            }
            catch (System.Exception ex)
            {
                ex.ToString();// avoid warn when compiling.
            }
        }

        public void Debug(string msgFmt, params object[] args)
        {
            //Console.WriteLine("Debug Test");
            if (m_log.IsDebugEnabled)
            {
                if (args.Length != 0)
                {
                    m_log.DebugFormat(msgFmt, args);
                }
                else
                {
                    m_log.Debug(msgFmt);
                }
            }
        }

        public void Warn(string msgFmt, params object[] args)
		{
            //Console.WriteLine("Debug Test");
            if (m_log.IsWarnEnabled)
            {
                if (args.Length !=0)
                {
                    m_log.WarnFormat(msgFmt, args);
                }
                else
                {
                    m_log.Warn(msgFmt);
                }
            }
		}

        public void Info(string msgFmt, params object[] args)
        {
            //Console.WriteLine("Debug Test");
            if (m_log.IsInfoEnabled)
            {
                if (args.Length != 0)
                {
                    m_log.InfoFormat(msgFmt, args);
                }
                else
                {
                    m_log.Info(msgFmt);
                }
            }
        }

        public void Error(string msgFmt, params object[] args)
        {
            //Console.WriteLine("Debug Test");
            if (m_log.IsErrorEnabled)
            {
                if (args.Length != 0)
                {
                    m_log.ErrorFormat(msgFmt, args);
                }
                else
                {
                    m_log.Error(msgFmt);
                }
            }
        }

        public void Fatal(string msgFmt, params object[] args)
        {
            //Console.WriteLine("Debug Test");
            if (m_log.IsFatalEnabled)
            {
                if (args.Length != 0)
                {
                    m_log.FatalFormat(msgFmt, args);
                }
                else
                {
                    m_log.Fatal(msgFmt);
                }
            }
        }

        public string ConfigFile
		{
			get
			{
				return configFile;
			}
			set
			{
				configFile = value;
			}
		}

        public bool WatchFlag
        {
            get
            {
                return watchFlag;
            }
            set
            {
                watchFlag = value;
            }
        }
	}
}
