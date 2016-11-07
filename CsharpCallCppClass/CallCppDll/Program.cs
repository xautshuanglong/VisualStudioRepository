using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CallCppDll
{
    class Program
    {
        static void Main(string[] args)
        {
            Person p = new Person();
            //p.SetName("shuanglong");
            p.SetAge(24);

            //System.Console.WriteLine("Name:" + p.GetName());
            System.Console.WriteLine("Age:" + p.GetAge());
        }
    }
}
