using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using log4net;
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
            System.Console.WriteLine("===================== Log4netConfigTest =====================");
            LogTool log = LogTool.Instance();

            for (int i = 0; i < 1; i++)
            {
                log.Debug("Debug Testing...");
                log.Debug("{0} --> {1}", "key", 321);
                log.Warn("Warn Testing ...");
                log.Info("Info Testing ...");
                log.Error("Error Testing ...");
                log.Fatal("Fatal Testing ...");
            }
            TestMethod();

            LogTool.Instance().Shutdown();
		}

        static void TestMethod()
        {
            LogTool log = LogTool.Instance();
            log.Debug("Inside TestMethod...");
            log.Info("Inside TestMethod...");
            log4net.ILog logger = LogTool.Instance().GetLogger();
            logger.Warn("Inside TestMethod");
        }
	}
}
