#include <iostream>

#include "CPerson.h"

CPerson::CPerson()
{
	m_name = new char[DEFAULT_NAME_LEN];
}

CPerson::~CPerson()
{
	delete m_name;
}

void CPerson::SetName(char *name)
{
	int nameLen = strlen(name);
	if (nameLen > DEFAULT_NAME_LEN)
	{
		nameLen = DEFAULT_NAME_LEN;
	}
	strcpy_s(m_name, nameLen, name);
}

char* CPerson::GetName()
{
	return m_name;
}

void CPerson::SetAge(int age)
{
	m_age = age;
}

int CPerson::GetAge()
{
	return m_age;
}