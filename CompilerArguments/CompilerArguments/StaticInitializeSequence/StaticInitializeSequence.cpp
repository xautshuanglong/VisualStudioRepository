#include "stdafx.h"

#include <iostream>

class TestA
{
public:
    TestA() { std::cout << "TestA::TestA()" << std::endl; }
    ~TestA() { std::cout << "TestA::~TestA()" << std::endl; }
};

class TestB
{
public:
    TestB() { std::cout << "TestB::TestB()" << std::endl; }
    ~TestB() { std::cout << "TestB::~TestB()" << std::endl; }
};

class TestC
{
public:
    TestC() { std::cout << "TestC::TestC()" << std::endl; }
    ~TestC() { std::cout << "TestC::~TestC()" << std::endl; }
};

static TestA gTestA;
static TestB gTestB;
static TestC gTestC;

int main()
{
    std::cout << "================ Inside Main Function ================" << std::endl;

    return 0;
}
