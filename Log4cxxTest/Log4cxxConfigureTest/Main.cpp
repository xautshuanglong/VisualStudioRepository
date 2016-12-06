#include <iostream>

#include "LogTool.h"

class ReturnObjTest;
ReturnObjTest* ReturnObjPointerTestFunc();
ReturnObjTest ReturnObjTestFunc();

class ReturnObjTest
{
public:
	ReturnObjTest() { std::cout << "ReturnObjTest constructor ..." << std::endl; }
	~ReturnObjTest() { std::cout << "ReturnObjTest destructor ..." << std::endl; }
	ReturnObjTest(const ReturnObjTest &originObj) { std::cout << "Call copy constructor ..." << std::endl; }
	ReturnObjTest& operator=(const ReturnObjTest &originObj) { std::cout << "Call assign function ..." << std::endl; return *this; }

	void IsAlive() { std::cout << "I'm alive." << std::endl; }
};

int main(int argc, char** argv)
{
	std::cout << "========================== Log4cxx Configure Test ==========================" << std::endl;
	LogTool* pLog = LogTool::GetInstance();

	pLog->Info("Without LocationInfo --> Info testing");
	pLog->Info(std::string("Without LocationInfo --> Hello"));
	pLog->Info(std::string("With LocationInfo --> Hello"), LOG4CXX_LOCATION);

	char pCharMsg[] = "Const char test";
	pLog->Info("Without LocationInfo --> %s,%d,%f,%d", pCharMsg, 5, 3.5, true);
	pLog->Info(LOG4CXX_LOCATION, "With LocationInfo --> %s,%d,%f,%d", pCharMsg, 5, 3.5, true);

	//log4cxx::spi::LocationInfo local("file", "method", 555);
	//std::cout << local.getFileName() << std::endl << local.getMethodName() << std::endl;

	//char fileName[100] = "fileName";
	//char methodName[100] = "methodName";
	//log4cxx::spi::LocationInfo localTest(fileName, methodName, 666);
	//std::cout << "localTest: " << localTest.getFileName() << "  " << localTest.getMethodName() << std::endl;

	//strcpy_s(methodName, 100, localTest.getMethodName().c_str());
	//log4cxx::spi::LocationInfo anotherLocal(localTest.getFileName(), methodName, 777);
	//std::cout << "anotherLocal: " << anotherLocal.getFileName() << "  " << anotherLocal.getMethodName() << std::endl;

	//log4cxx::spi::LocationInfo copyConstruct(localTest);
	//std::cout << "copyConstruct: " << copyConstruct.getFileName() << "  " << copyConstruct.getMethodName() << std::endl;

	std::cout << "========================== Return object Test ==========================" << std::endl;
	//ReturnObjTest *pTemp = ReturnObjPointerTestFunc();
	//std::cout << "Inside main: ";
	//pTemp->IsAlive();
	//delete pTemp;

	//std::cout << "Copyt Test" << std::endl;
	//ReturnObjTest copyTest(*pTemp);

	//std::cout << "Assignment Test" << std::endl;
	//ReturnObjTest assignTest;
	//assignTest= copyTest;

	//ReturnObjTest retVate;
	//retVate = ReturnObjTestFunc();
	//retVate.IsAlive();

	return 0;
}

ReturnObjTest* ReturnObjPointerTestFunc()
{
	ReturnObjTest *pRetObj = new ReturnObjTest();
	std::cout << "Inside ReturnObjPointerTestFunc: ";
	pRetObj->IsAlive();

	return pRetObj;
}

ReturnObjTest ReturnObjTestFunc()
{
	ReturnObjTest retValue;
	std::cout << "Inside ReturnObjTestFunc: ";
	retValue.IsAlive();

	return retValue;
}
