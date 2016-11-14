#include <iostream>
#include <iomanip>
#include <SimpleMathMethod.h>

int main(int argc, char** argv)
{
	std::cout << "============================ Static Library Test ============================" << std::endl;

	std::cout << "3+5 = " << AddFunc(3, 5) << std::endl;
	std::cout << "8-5 = " << MinusFunc(8, 5) << std::endl;

	ClassTest classTest;
	std::cout << "2+7 = " << classTest.AddFunc(2, 7) << std::endl;
	std::cout << "7-2 = " << classTest.MinusFunc(7, 2) << std::endl;

	return 0;
}
