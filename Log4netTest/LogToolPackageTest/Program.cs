using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LogToolPackageTest
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("===================== LogTool Package Test =====================");

            LogTool log = LogTool.Instance();
            log.Debug("test");
            log.Info("Info Test");
            log.Warn("{0} --> {1}", "key", "value");

            TestMethod();
        }

        static void TestMethod()
        {
            LogTool log = LogTool.Instance();
            log.Debug("Inside TestMethod()");
            log.Error("{0} --> {1}", "key", 12345);
            log.Fatal("Fatal Testing");
            log.Fatal("{1} <-- {0}", "key", "value");
        }
    }
}
