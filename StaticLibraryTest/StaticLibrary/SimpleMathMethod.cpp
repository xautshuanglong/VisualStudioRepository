#include <iostream>

#include "SimpleMathMethod.h"

int AddFunc(int a, int b)
{
	return a + b;
}

int MinusFunc(int a, int b)
{
	return a - b;
}

ClassTest::ClassTest()
{
	std::cout << "Inside ClassTest::ClassTest()" << std::endl;
}

ClassTest::~ClassTest()
{
	std::cout << "Inside ClassTest::~ClassTest()" << std::endl;
}

int ClassTest::AddFunc(int a, int b)
{
	return a + b;
}

int ClassTest::MinusFunc(int a, int b)
{
	return a - b;
}
