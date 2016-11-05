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
using log4net.Layout;

namespace Log4netTest
{
	class Program
	{
		static void Main(string[] args)
		{
            System.Console.WriteLine("==================== Log4netTest ====================");
			PatternLayout pl = new PatternLayout("%d [%-5p] %class.%method -> %m%n");

			LevelRangeFilter lrf = new LevelRangeFilter();
			lrf.LevelMax = Level.Fatal;
			lrf.LevelMin = Level.Debug;
			lrf.ActivateOptions();

			FileAppender fa = new FileAppender();
			fa.Layout = pl;
			fa.File = @".\\testFile.log";
			fa.AddFilter(lrf);
			fa.ActivateOptions();
			//fa.AppendToFile = true;
			//BasicConfigurator.Configure(fa);

            ConsoleAppender ca = new ConsoleAppender();
            ca.Layout = pl;
            //BasicConfigurator.Configure(ca);
            IAppender []appenders = { fa, ca };
            BasicConfigurator.Configure(appenders);

            ILog log = LogManager.GetLogger("root");

			log.Debug("Debug Testing...");
			log.Warn("Warn Testing ...");
			log.Info("Info Testing ...");
			log.Error("Error Testing ...");
			log.Fatal("Fatal Testing ...");

            System.Console.ReadLine();
		}
	}
}
