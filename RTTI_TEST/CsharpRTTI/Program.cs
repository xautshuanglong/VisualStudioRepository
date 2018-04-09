using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsharpRTTI
{
    class BaseClass
    {
        public void Test() { Console.WriteLine("BaseClass::Test"); }
        public virtual void VirtualFunc() { Console.WriteLine("BaseClass::VirtualFunc"); }
    }

    class DerivedClass : BaseClass
    {
        public new void Test() { Console.WriteLine("DerivedClass::Test"); }
        public override void VirtualFunc() { Console.WriteLine("DerivedClass::VirtualFunc"); }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("========================= RTTI Testing ========================");

            BaseClass bc = new BaseClass();
            DerivedClass dc = new DerivedClass();

            bc.Test();
            bc.VirtualFunc();
            Console.Write("bc is BaseClass? {0}  bc is DerivedClass? {1}", bc is BaseClass, bc is DerivedClass);
            Console.Write(Environment.NewLine);

            dc.Test();
            dc.VirtualFunc();
            Console.Write("dc is BaseClass? {0}  dc is DerivedClass? {1}", dc is BaseClass, dc is DerivedClass);
            Console.Write(Environment.NewLine);

            BaseClass bcdc = new DerivedClass();
            bcdc.Test();
            bcdc.VirtualFunc();
            Console.Write("bcdc is BaseClass? {0}  bcdc is DerivedClass? {1}", bcdc is BaseClass, bcdc is DerivedClass);
            Console.Write(Environment.NewLine);
        }
    }
}
