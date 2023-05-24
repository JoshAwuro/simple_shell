#include "shell.h"

int slash(char *command){
	int i = 0;

	while (command[i])
	{
		if (command[0] == '/')
		{
			printf("%d\n", command[0]);
			return 1;
		}
		
		i++;
	}
	return 0;
}

int check_exit(char *str1, char *str2)
{
	int josh;
	
	for (josh = 0; (*str1 != '\0' && *str2 != '\0') && *str1 == *str2; str1++)
		{
			if (josh == 3)
				break;
			josh++;
			str2++;
		}

	return (*str1 - *str2);
}

int check_env(char *str1, char *str2)
{
	int josh;

	for (josh = 0; (*str1 != '\0' && *str2 != '\0') && *str1 == *str2; str1++)
	{
		if (josh == 2)
			break;
		josh++;
		str2++;
	}

	return (*str1 - *str2);
}

char **strput(char *arg)
{
	char **BUFFER;
	char *div;
	int josh = 0;
	char *deals = " \t\n";

	BUFFER = malloc(sizeof(char *) * 1024);

	div = strtok(arg, deals);

	while (div != NULL)
	{
		BUFFER[josh] = div;
		josh++;
		div = strtok(NULL, deals);
	}
	perform(BUFFER);
	return BUFFER;
}

void controlled(int signal)
{
	(void) signal;
	write(1, "\n$ ", 3);
}
