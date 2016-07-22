#include <stdio.h>

void ParseCommandLineArguments(int argc, char **argv, bool displayArgs = true);

int main(int argc, char **argv)
{
	printf("=========== OutputFormatDebugString ============\n");
	ParseCommandLineArguments(argc, argv);

	return 0;
}

void ParseCommandLineArguments(int argc, char **argv, bool displayArgs)
{
	if (displayArgs)
	{
		printf("Arguments of£º\n¡¾%s¡¿\n", argv[0]);
		for (int i = 1; i < argc; i++)
		{
			printf("argv[%d]: %s\n", i, argv[i]);
		}
	}
}
