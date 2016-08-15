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

//[assembly: XmlConfigurator(Watch = true)]// 在 App.config 中配置 log4net
//[assembly: XmlConfigurator(ConfigFile = @"..\\..\\Log4netConfig.xml", Watch = true)]

namespace Log4netConfigTest
{
	class Program
	{
		static void Main(string[] args)
		{
            LogTool log = LogTool.Instance();
		    
			log.Debug("Debug Testing...");
            log.Debug("{0} --> {1}", "key", 321);
			log.Warn("Warn Testing ...");
			log.Info("Info Testing ...");
			log.Error("Error Testing ...");
			log.Fatal("Fatal Testing ...");
			
			LogManager.Shutdown();
		}
	}
}
