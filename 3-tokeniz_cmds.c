#include "shell.h"
/**
 * tokeniz - function that Breaks a string into a sequence of tokens based on
 * a specified delimiter.
 * @line: the commands line.
 * Return: commands as tokens and NULL if it fails.
 */
char **tokeniz(char *line)
{
	int length = 0;
	int capacity = 16;
	char **tokens;
	char *token;

	tokens = malloc(capacity * sizeof(char *));
	if (tokens == NULL)
	{
		free(tokens);
		return (NULL);
	}

	token = _strtok(line, " \n");
	while (token != NULL)
	{
		tokens[length] = token;
		length++;

		if (length >= capacity)
		{
			capacity += capacity;
			tokens = realloc(tokens, capacity * sizeof(char *));
			if (tokens == NULL)
			{
				free(tokens);
				return (NULL);
			}
		}
		token = _strtok(NULL, " \n");
	}

	tokens[length] = NULL;
	return (tokens);
}
