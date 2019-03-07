#include "stdafx.h"
#include "OutFileTestC.h"
#include <iostream>

#pragma init_seg(lib)
static OutFileTestC gOutFileTestC;

OutFileTestC::OutFileTestC()
{
    std::cout << "OutFileTestC::OutFileTestC()" << std::endl;
}

OutFileTestC::~OutFileTestC()
{
    std::cout << "OutFileTestC::~OutFileTestC()" << std::endl;
}
