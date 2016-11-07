#pragma once
#include <CPerson.h>

//#define LX_DLL_CLASS_EXPORTS
using namespace System;

public ref class Person
{
	private:
		String^ m_pName;
		int m_age;

		CPerson* m_pCPerson;
public:
	Person();
	~Person();

	void SetName(String^ name);
	String^ GetName();

	void SetAge(int age);
	int GetAge();
};