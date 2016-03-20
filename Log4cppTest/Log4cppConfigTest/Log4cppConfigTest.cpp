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
		PropertyConfigurator::configure("..//config//log4cpp.ini");
	}
	catch (ConfigureFailure& e)
	{
		cout << "Configure Problem: " << e.what() << endl;
		return -1;
	}

	Category& root = Category::getRoot();
	Category& sub1 = Category::getInstance("file");
	Category& sub2 = Category::getInstance("rolling");

	NDC::push("Log4cppConfigTest");

	sub1.info("sub1 info testing");
	sub1.debug("sub1 info testing");
	sub1.warn("sub1 info testing");
	sub1.error("sub1 info testing");

	sub2.info("sub2 alert testing");
	sub2.debug("sub1 info testing");
	sub2.warn("sub1 info testing");
	sub2.error("sub1 info testing");

	return 0;
}