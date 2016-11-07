using log4net;
using log4net.Appender;
using log4net.Config;
using log4net.Core;
using log4net.Filter;
using log4net.Layout;
using log4net.Repository.Hierarchy;
using log4net.Util;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

/************************************************************************/
/*        OFF -> FATAL -> ERROR -> WARN -> INFO -> DEBUG -> ALL         */
/************************************************************************/

namespace LogToolPackageTest
{
    public sealed class LogTool
    {
        private static volatile LogTool logInstance = null;
        private static readonly object SynObj = new object();

        private static string configFile = "Log4netConfig.xml";
        private static string logsOutDir = "logs";

        private static readonly Type thisDeclareType = typeof(LogTool);

        private ILog m_log;

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
                        logInstance.CheckLogDirectoryAndConfig();
                        FileInfo file = logInstance.LoadConfigFile();
                        if (file == null)
                        {
                            System.Console.WriteLine("file == null");
                            logInstance.BasicConfigLog4net();
                        } 
                        else
                        {
                            XmlConfigurator.Configure(file);
                            ILog logger = LogManager.GetLogger("root");
                            logInstance.m_log = LogManager.GetLogger("root");
                            if (logInstance.m_log.Logger.Repository.Configured == false)
                            {
                                logInstance.BasicConfigLog4net();
                                logInstance.m_log = LogManager.GetLogger("root");
                            }
                            logInstance.ChangeFilterForRelease();
                        }
                    }
                }
            }
            return logInstance;
        }

        /************************************************************************/
        /*  改变日志等级，防止篡改配置文件输出敏感信息                             */
        /************************************************************************/
        private void ChangeFilterForRelease()
        {
#if !DEBUG
            IAppender[] appenders = m_log.Logger.Repository.GetAppenders();

            LevelRangeFilter levelRange = new LevelRangeFilter();
            levelRange.LevelMin = Level.Info;
            levelRange.LevelMax = Level.Fatal;

            foreach (IAppender appenderItem in appenders)
            {
                if (appenderItem is ConsoleAppender)
                {
                    ConsoleAppender tempAppender = (ConsoleAppender)appenderItem;
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
                }
                else if (appenderItem is RollingFileAppender)// RollingFileAppender is extends FileAppender,so it should be judged before FileAppender.
                {
                    RollingFileAppender tempAppender = (RollingFileAppender)appenderItem;
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
                    //tempAppender.File = logsOutDir + "\\RollingFile.log";
                }
                else if (appenderItem is FileAppender)
                {
                    FileAppender tempAppender = (FileAppender)appenderItem;
                    tempAppender.ClearFilters();
                    tempAppender.AddFilter(levelRange);
                    //tempAppender.File = logsOutDir + "\\TempFile.log";
                }
                else
                {
                    // For security, remove all other appenders.
                    Logger logger = (Logger)m_log.Logger;
                    logger.Parent.RemoveAppender(appenderItem);
                }
            }
#endif
        }

        /************************************************************************/
        /* 检查日志输出路径是否存在，不错字则创建该目录，以存放日志文件。           */
        /************************************************************************/
        private bool CheckLogDirectoryAndConfig()
        {
            string curExeFilename = Process.GetCurrentProcess().MainModule.FileName;
            string curExeDir = curExeFilename.Substring(0, curExeFilename.LastIndexOf("\\")+1);
            string logsDir = curExeDir + logsOutDir;
            logsOutDir = logsDir;// save path to place log files.
            configFile = curExeDir + configFile;

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
                return false;
            }

            return true;
        }

        private FileInfo LoadConfigFile()
        {
            FileInfo resValue = null;
            if (File.Exists(configFile))
            {
                try
                {
                    resValue = new FileInfo(configFile);
                }
                catch (System.Exception ex)
                {
                    ex.ToString();
                    resValue = null;
                }
            }

            return resValue;
        }

        private void BasicConfigLog4net()
        {
            PatternLayout pl = new PatternLayout("%date{HH:mm:ss.fff} [%-5level] %class.%method - %message%newline");

            LevelRangeFilter lrf = new LevelRangeFilter();
            lrf.LevelMax = Level.Fatal;
            lrf.LevelMin = Level.Debug;
            lrf.ActivateOptions();

            FileAppender fa = new FileAppender();
            fa.Layout = pl;
            fa.File = @".\\logs\\TempFile.log";
            fa.AddFilter(lrf);
            fa.ActivateOptions();

            RollingFileAppender rfa = new RollingFileAppender();
            rfa.Layout = pl;
            rfa.File = @".\\logs\\RollingFile.log";
            rfa.RollingStyle = RollingFileAppender.RollingMode.Size;
            rfa.MaximumFileSize = "1KB";
            rfa.CountDirection = -1;
            rfa.MaxSizeRollBackups = 5;
            rfa.AppendToFile = true;
            rfa.AddFilter(lrf);
            rfa.ActivateOptions();

            ConsoleAppender ca = new ConsoleAppender();
            ca.Layout = pl;
            IAppender[] appenders = { fa, rfa, ca };
            BasicConfigurator.Configure(appenders);
        }

        public void Debug(string message)
        {
            m_log.Logger.Log(thisDeclareType, Level.Debug, message, null);
        }

        public void Debug(string format, params object[] args)
        {
            m_log.Logger.Log(thisDeclareType, Level.Debug, String.Format(format,args), null);
        }

        public void Info(string message)
        {
            m_log.Logger.Log(thisDeclareType, Level.Info, message, null);
        }

        public void Info(string format, params object[] args)
        {
            m_log.Logger.Log(thisDeclareType, Level.Info, String.Format(format, args), null);
        }

        public void Warn(string message)
        {
            m_log.Logger.Log(thisDeclareType, Level.Warn, message, null);
        }

        public void Warn(string format, params object[] args)
        {
            m_log.Logger.Log(thisDeclareType, Level.Warn, String.Format(format, args), null);
        }

        public void Error(string message)
        {
            m_log.Logger.Log(thisDeclareType, Level.Error, message, null);
        }

        public void Error(string format, params object[] args)
        {
            m_log.Logger.Log(thisDeclareType, Level.Error, String.Format(format, args), null);
        }

        public void Fatal(string message)
        {
            m_log.Logger.Log(thisDeclareType, Level.Fatal, message, null);
        }

        public void Fatal(string format, params object[] args)
        {
            m_log.Logger.Log(thisDeclareType, Level.Fatal, String.Format(format, args), null);
        }
    }

    //interface IMyLog:ILog
    //{
    //    void Debug(string message);
    //    void Debug(string format, object[] args);
    //}

    //class MyLogImpl:LogImpl,IMyLog
    //{
    //    private readonly static Type thisDeclaringType = typeof(LogTool);

    //    public MyLogImpl(ILogger logger):base(logger)
    //    {
    //    }

    //    public void Debug(string message)
    //    {
    //        Logger.Log(thisDeclaringType, Level.Info, message, null);
    //    }

    //    public void Debug(string format, object[] args)
    //    {
    //        Logger.Log(thisDeclaringType, Level.Info, new SystemStringFormat(CultureInfo.InvariantCulture, format, args), null);
    //    }
    //}

    //class MyLogManager
    //{
    //    private static readonly WrapperMap m_wrapperMap = new WrapperMap(new WrapperCreationHandler(MyWrapperCreationHandler));

    //    public static IMyLog Exists(string name)
    //    {
    //        return Exists(Assembly.GetCallingAssembly(), name);
    //    }

    //    public static IMyLog Exists(string domain, string name)
    //    {
    //        return WrapLogger(LoggerManager.Exists(domain, name));
    //    }

    //    public static IMyLog Exists(Assembly assembly, string name)
    //    {
    //        return WrapLogger(LoggerManager.Exists(assembly, name));
    //    }

    //    public static IMyLog GetLogger(string name)
    //    {
    //        return GetLogger(Assembly.GetCallingAssembly(), name);
    //    }

    //    public static IMyLog GetLogger(string domain, string name)
    //    {
    //        return WrapLogger(LoggerManager.GetLogger(domain, name));
    //    }

    //    public static IMyLog GetLogger(Assembly assembly, string name)
    //    {
    //        return WrapLogger(LoggerManager.GetLogger(assembly, name));
    //    }

    //    private static IMyLog WrapLogger(ILogger logger)
    //    {
    //        return (IMyLog)m_wrapperMap.GetWrapper(logger);
    //    }

    //    private static ILoggerWrapper MyWrapperCreationHandler(ILogger logger)
    //    {
    //        return new MyLogImpl(logger);
    //    }
    //}
}
