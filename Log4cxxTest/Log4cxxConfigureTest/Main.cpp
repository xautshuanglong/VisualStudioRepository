#include <iostream>

#include "LogTool.h"

class ReturnObjTest;

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool* pLog = LogTool::GetInstance();

	pLog->Info("Info testing");
	pLog->Info(std::string("Hello"));
	pLog->Info(std::string("Hello"), LOG4CXX_LOCATION);

	char pCharMsg[] = "Const char test";
	pLog->Info("%s,%d,%f,%d", pCharMsg, 5, 3.5, true);
	pLog->Info(LOG4CXX_LOCATION, "%s,%d,%f,%d", pCharMsg, 5, 3.5, true);

	log4cxx::spi::LocationInfo local("file", "method", 555);
	std::cout << local.getFileName() << std::endl << local.getMethodName() << std::endl;

	char fileName[100] = "fileName";
	char methodName[100] = "methodName";
	log4cxx::spi::LocationInfo localTest(fileName, methodName, 666);
	std::cout << "localTest: " << localTest.getFileName() << "  " << localTest.getMethodName() << std::endl;

	strcpy_s(methodName, 100, localTest.getMethodName().c_str());
	log4cxx::spi::LocationInfo anotherLocal(localTest.getFileName(), methodName, 777);
	std::cout << "anotherLocal: " << anotherLocal.getFileName() << "  " << anotherLocal.getMethodName() << std::endl;

	log4cxx::spi::LocationInfo copyConstruct(localTest);
	std::cout << "copyConstruct: " << copyConstruct.getFileName() << "  " << copyConstruct.getMethodName() << std::endl;

	return 0;
}

class ReturnObjTest
{
public:
	ReturnObjTest() { std::cout << "ReturnObjTest constructor ..." << std::endl; }
	~ReturnObjTest() { std::cout << "ReturnObjTest destructor ..." << std::endl; }

private:
};
