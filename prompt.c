#include "main.h"

/**
 * prompt - Displays the shell prompt and handles user input
 * @av: command-line arguments
 * @env: environment variables
 */

void prompt(char **av, char **env)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t num_char;
	char *argv[MAX_COMMAND];
	int path_index = 0;
	char *path_parts[MAX_COMMAND];
	int argc;
	char *token;

	(void) av;

	init_path(&path_index, path_parts);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		num_char = getline(&lineptr, &n, stdin);
		if (num_char == -1)
		{
			free(lineptr);
			exit(EXIT_FAILURE);
		}

		lineptr[_strcspn(lineptr, "\n")] = '\0'; /* Remove newline */

		argc = 0;
		token = strtok(lineptr, " ");
		while (token != NULL && argc < MAX_COMMAND - 1)
		{
			argv[argc++] = token;
			token = strtok(NULL, " ");
		}
		argv[argc] = NULL; /* Set the last element to NULL */
		handle_cmd(argv, env, path_parts, path_index);
	}
}
