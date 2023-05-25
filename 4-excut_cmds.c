#include "shell.h"
/**
 * excut_cmd - function that executes the program referred to by (path).
 * @path: binary executable.
 * @cmd: an array of pointers to strings passed to the new program
 * as its command-line arguments.
 * Return: On success, return 0, on error -1 is returned
 */
int excut_cmd(char *path, char **cmd)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		status = execve(path, cmd, environ);
		if (status == -1)
			return (1);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do {
		waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}
/**
 * access_path - function that checks whether the calling process
 * can access the file cmd.
 * @cmd: the file of the command.
 * Return: On success, zero is returned. On error -1 is returned;
 */
int access_path(const char *cmd)
{
	int result = access(cmd, X_OK);

	if (result == -1)
	{
		return (-1);
	}
	else
		return (0);
}
/**
 * find_command_path - function that look for commands.
 * @cmd: the command.
 * Return: excutable (the path to the command if it exist),
 * and NULL if its not.
 */
char *find_command_path(const char *cmd)
{
	char *excutable = NULL;

	if (cmd[0] == '/')
	{
		if (access_path(cmd) == 0)
		{
			excutable = _strdup((char *) cmd);
			return (excutable);
		}
	}
	else
	{
		char *path = _getenv("PATH");
		char *path_copy = _strdup(path);
		char *dir;

		dir = strtok(path_copy, ":");
		while (dir != NULL)
		{
			excutable = malloc(_strlen(dir) + _strlen(cmd) + 2);
			if (excutable == NULL)
			{
				free(excutable);
				return (NULL);
			}
			_strcpy(excutable, dir);
			_strcat(excutable, "/");
			_strcat(excutable, (char *) cmd);
			if (access_path(excutable) == 0)
			{
				free(path_copy);
				return (excutable);
			}
			free(excutable);
			dir = strtok(NULL, ":");
		}
		free(path_copy);
	}

	return (NULL);
}

/**
 * excutcmd - function that excut the commands.
 * @cmd: the commands.
 * Return: On success, return 0, on error 1 is returned.
 */
int excutcmd(char **cmd)
{
	char *path;
	int i, comp;
	built_in builtin_cmds[] = {
		{"exit", end},
		{"env", env},
		{NULL, NULL}
		};

	/* check if its a builtin command */
	for (i = 0; builtin_cmds[i].name != NULL; i++)
	{
		comp = _strncmp(cmd[0], builtin_cmds[i].name,
				_strlen(builtin_cmds[i].name));
		if (comp == 0)
			return (builtin_cmds[i].f(cmd));
	}

	path = find_command_path(cmd[0]);
	if (path != NULL)
	{
		if (excut_cmd(path, cmd) == 0)
		{
			free(path);
			return (0);
		}
		free(path);
		return (1);
	}
	return (1);
}
