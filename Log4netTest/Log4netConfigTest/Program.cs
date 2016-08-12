using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using log4net.Config;

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

			log.Debug(log.Logger.Name);
			
			log.Debug("Debug Testing...");
			log.Warn("Warn Testing ...");
			log.Info("Info Testing ...");
			log.Error("Error Testing ...");
			log.Fatal("Fatal Testing ...");
			
			LogManager.Shutdown();
		}
	}
}
