#include "shell.h"
/**
 * space_check - function that check for spaces.
 * @line: read line.
 * Return: 0 foound a character, 1 Null line.
 */
int space_check(char *line)
{
	int i;

	for (i = 0; line[i] != '\n'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			return (0);
		}
	}
	return (1);
}
/**
 * read_stdin - read a line from the stdin.
 * Return: pointer points to the line.
 */
char *read_stdin(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	int len;

	len = getline(&lineptr, &n, stdin);
	if (len == EOF)
	{
		/* in case of “end of file” condition (Ctrl+D)*/
		write(STDOUT_FILENO, "\n", 1);
		free(lineptr);
		exit(EXIT_SUCCESS);
	}
	if (len == -1)
	{
		perror("getline: ");
		exit(EXIT_FAILURE);
	}

	if (space_check(lineptr) == 1)
	{
		free(lineptr);
		/* in case of empty line (nothing been entred)*/
		return (NULL);
	}

	return (lineptr);
}
