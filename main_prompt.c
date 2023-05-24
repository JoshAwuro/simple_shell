#include "shell.h"

void prompt(void)
{
	for (;;)
	{
		char *input = NULL, **environ;
		pid_t child_pid;
		int stat, br;
		size_t sb = 0;

		hold("$ ");
		br = getline(&input, &sb, stdin);
		if (br == -1)
			exit(98);
		if (env_check(input, "exit") == 0)
			exit(0);
		if (env_check(input, "env") == 0)
		{
			while (*environ != NULL)
			{
				if (!(_strcmp(*environ, "USER")) || 
						!(_strcmp(*environ, "LANGUAGE")) ||
						!(_strcmp(*environ, "SESSION")) ||
						!(_strcmp(*environ, "COMPIZ_CONFIG_PROFILE")) ||
						!(_strcmp(*environ, "SHLV")) ||
						!(_strcmp(*environ, "HOME")) ||
						!(_strcmp(*environ, "C_IS")) ||
						!(_strcmp(*environ, "DESKTOP_SESSION")) ||
						!(_strcmp(*environ, "LOGNAME")) ||
						!(_strcmp(*environ, "TERM")) ||
						!(_strcmp(*environ, "PATH")))
				{
					hold(*environ), hold("\n");
				}
				environ++;
			}
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Error");
		}
		if (child_pid == 0)
		{
			strput(input);
		}
		else
		{
			wait(&stat);
		}
}
