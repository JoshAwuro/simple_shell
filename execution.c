#include "shell.h"

void perform(char **command)
{
	char *cd;
	char *arg = (*(command + 1));
	char *f_s = "/";
	char *f_c;
	char *p_var = *command;
	char *argv[4];
	if ((access(command[0], F_OK) == 0))
	{
		argv[0] = command[0];
		argv[1] = arg;
		argv[2] = ".";
		argv[3] = NULL;
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		f_c = command_finder(p_var);
		f_s = concat_str(f_c, f_s);
		cd = concat_str(f_s, *command);
		argv[0] = cd;
		argv[1] = arg;
		argv[2] = ".";
		argv[3] = NULL;
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
}
