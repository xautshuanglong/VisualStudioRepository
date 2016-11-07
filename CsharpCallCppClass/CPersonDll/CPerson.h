#pragma once

#define DEFAULT_NAME_LEN 50

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus


	class _declspec(dllexport) CPerson
	{
	private:
		char* m_name;
		int m_age;

	public:
		CPerson();
		~CPerson();

		void SetName(char *name);
		char* GetName();

		void SetAge(int age);
		int GetAge();
	};

#ifdef _cplusplus
}
#endif // _cplusplus