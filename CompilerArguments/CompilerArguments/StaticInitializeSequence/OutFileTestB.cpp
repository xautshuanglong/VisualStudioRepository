#include "stdafx.h"
#include "OutFileTestB.h"
#include <iostream>

#pragma init_seg(compiler)
static OutFileTestB gOutFileTestB;

OutFileTestB::OutFileTestB()
{
    std::cout << "OutFileTestB::OutFileTestB()" << std::endl;
}

OutFileTestB::~OutFileTestB()
{
    std::cout << "OutFileTestB::~OutFileTestB()" << std::endl;
}
