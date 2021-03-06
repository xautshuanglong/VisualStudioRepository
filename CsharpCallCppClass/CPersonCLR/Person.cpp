#include <vcclr.h>
#include <iostream>
#include "Person.h"

Person::Person()
{
	m_pCPerson = new CPerson();
}

Person::~Person()
{
	delete m_pCPerson;
}

void Person::SetName(String^ name)
{
	pin_ptr<const Char> pName = PtrToStringChars(name);
	char tempName[DEFAULT_NAME_LEN];
	int i = 0;
	for (i=0;*(pName+i)!='\0';i++)
	{
		tempName[i] = *(pName + i);
	}
	tempName[i] = '\0';
	m_pCPerson->SetName(tempName);
}

String ^Person::GetName()
{
	return gcnew String(m_pCPerson->GetName());
}

void Person::SetAge(int age)
{
	m_pCPerson->SetAge(age);
}

int Person::GetAge()
{
	return m_pCPerson->GetAge();
}