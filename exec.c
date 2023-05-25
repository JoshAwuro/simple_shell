#include "main.h"
/**
 * build_cmd_path - constructs the full path of a command
 * @dir: the directory path
 * @command: the command name
 *
 * Return: a pointer to the constructed full path
 */

char *build_cmd_path(char *dir, char *command)
{
	char *full_path;

	full_path = malloc(_strlen(dir) + _strlen(command) + 2); /* 1=/n & 1="/"*/
	_strcpy(full_path, dir);
	_strcat(full_path, "/");
	_strcat(full_path, command);

	return (full_path);
}

/**
 * print_environment - prints the curr environ
 * @env: array of envir vars
 *
 * function prints each env var in the array.
 */

void print_environment(char **env)
{
	char **envp = env;

	for (; *envp; envp++)
	{
		_puts(*envp);
	}
}

/**
 * find_cmd_path - constructs the full path for a command
 * @command: the command name
 * @path_parts: array of path dirs
 * @path_index: number of path dirs
 *
 * Return: pointer to full path, or NULL if not found
 */

char *find_cmd_path(char *command, char **path_parts, int path_index)
{
	char *cmd_path = NULL;

	if (_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
		{
			cmd_path = _strdup(command);
		}
	}
	else
	{
		int i;

		for (i = 0; i < path_index; i++)
		{
			char *temp_path = build_cmd_path(path_parts[i], command);

			if (access(temp_path, F_OK) == 0)
			{
				cmd_path = temp_path;
				break;
			}
			else
			{
				free(temp_path);
			}
		}
	}

	return (cmd_path);
}
/**
 * exec_cmd - forks a child process and executes the cmd
 * @cmd_path: the full path of the cmd
 * @argv: array of cmnd arguments
 * @env: array of env vars
 *
 * function forks a child process and executes the command.
 */
void exec_cmd(char *cmd_path, char **argv, char **env)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(cmd_path, argv, env) == -1)
		{
			perror("Error: Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free(cmd_path);
}
/**
 * handle_cmd - handles cmd execution
 * @argv: array of cmd arguments
 * @env: environment variables
 * @path_parts: array of PATH directories
 * @path_index: no of PATH directories
 */
void handle_cmd(char **argv, char **env, char **path_parts, int path_index)
{
	char *err_msg;

	if (_strcmp(argv[0], "exit") == 0)
	{
		_puts("Exiting shell...");
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
		print_environment(env);
	}
	else
	{
		char *cmd_path = find_cmd_path(argv[0], path_parts, path_index);

		if (cmd_path == NULL)
		{
			size_t err_msg_len = _strlen(argv[0]) + _strlen(": command not found") + 1;

			err_msg = malloc(err_msg_len);
			if (err_msg == NULL)
			{
				perror("Error: Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			_strcpy(err_msg, argv[0]);
			_strcat(err_msg, ": command not found");

			_puts(err_msg);
			free(err_msg);
		}
		else
		{
			exec_cmd(cmd_path, argv, env);
		}
	}
}

