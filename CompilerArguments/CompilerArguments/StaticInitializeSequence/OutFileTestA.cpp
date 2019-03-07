#include "stdafx.h"
#include "OutFileTestA.h"
#include <iostream>

#pragma init_seg(user)
static OutFileTestA gOutFileTestA;

OutFileTestA::OutFileTestA()
{
    std::cout << "OutFileTestA::OutFileTestA()" << std::endl;
}

OutFileTestA::~OutFileTestA()
{
    std::cout << "OutFileTestA::~OutFileTestA()" << std::endl;
}
