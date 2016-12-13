#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PropertyConfigurator.hh>

using namespace std;
using namespace log4cpp;

int main(int argc, char* argv[])
{
	//int i = 0;
	//for (i = 0; i < argc; i++)
	//{
	//	cout << "argv[" << i << "]: " << *(argv+i) << endl;
	//}
	try
	{
		PropertyConfigurator::configure("./log4cpp.ini");
	}
	catch (ConfigureFailure& e)
	{
		cout << "Configure Problem: " << e.what() << endl;
		return -1;
	}

	Category& console = Category::getInstance("console");
	Category& sub1 = Category::getInstance("tempfile");
	Category& sub2 = Category::getInstance("rolling");

	NDC::push("Log4cppConfigTest");

	sub1.info("sub1 info testing");
	sub1.debug("sub1 debug testing");
	sub1.warn("sub1 warn testing");
	sub1.error("sub1 error testing");

	sub2.info("sub2 info testing");
	sub2.debug("sub2 debug testing");
	sub2.warn("sub2 warn testing");
	sub2.error("sub2 error testing");

	console.info("console info test");
	console.warn("console warn test");

	return 0;
}