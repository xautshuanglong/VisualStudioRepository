#include <iostream>

#include "MathMethod.h"

int main(int argc, char **argv)
{
	std::cout << "======================= Reference Dll Test =======================" << std::endl;
	std::cout << "3+5 = " << AddFunc(3, 5) << std::endl;
	std::cout << "3-5 = " << MinFunc(3, 5) << std::endl;

	return 0;
}
