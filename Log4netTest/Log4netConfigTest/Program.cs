using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using log4net.Appender;
using log4net.Config;
using log4net.Core;
using log4net.Filter;

//[assembly: XmlConfigurator(Watch = true)]
[assembly: XmlConfigurator(ConfigFile = @"..\\..\\Log4netConfig.xml", Watch = true)]
//[assembly: XmlConfigurator(ConfigFile = "Log4netConfig", ConfigFileExtension = "xml", Watch = true)]

namespace Log4netConfigTest
{
	class Program
	{
		static void Main(string[] args)
		{
			ILog log = LogManager.GetLogger("root");
#if !DEBUG
			IAppender[] appenders = log.Logger.Repository.GetAppenders();

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
				else if (appenderItem is FileAppender)
				{
					FileAppender tempAppender = (FileAppender)appenderItem;
					tempAppender.ClearFilters();
					tempAppender.AddFilter(levelRange);
				}
				else if (appenderItem is RollingFileAppender)
				{
					RollingFileAppender tempAppender = (RollingFileAppender)appenderItem;
					tempAppender.ClearFilters();
					tempAppender.AddFilter(levelRange);
				}
			}
#endif

			log.Debug("Debug Testing...");
			log.Warn("Warn Testing ...");
			log.Info("Info Testing ...");
			log.Error("Error Testing ...");
			log.Fatal("Fatal Testing ...");
			
			LogManager.Shutdown();
		}
	}
}
