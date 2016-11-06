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

            TestMethod();
        }

        static void TestMethod()
        {
            LogTool log = LogTool.Instance();
            log.Debug("Inside TestMethod()");
        }
    }
}
