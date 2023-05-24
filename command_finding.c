#include "shell.h"
#include <dirent.h>

char *find_command(char *command)
{
	DIR *dir;
	struct dirent *start;
	char *env, checks, **st = malloc(sizeof(char) * 1024);
	char **sep = malloc(sizeof(char) * 1024);
	int j;
		
	while (*environ != NULL )
	{
		if (!strcmp(*environ, "PATH"))
		{
			*st = *environ;
			
			for (j = 0; j < 9; j++, sep++, st++)
			{
				*sep = strtok(*st, ":='PATH'");
				dir = opendir(*sep);
				if (dir == NULL)
					perror("Can't read directory");
				while ((start = readdir(dir)) != NULL)
				{
					env = start->d_name;
					checks = strcmp(env, command);
					if (checks == 0)
					{
						return (*sep);
					}
					if (env == NULL)
					{
						perror("Error");
					}
				}
			}
		}
		environ++;
	}
	return ("Error: File not found");
}
