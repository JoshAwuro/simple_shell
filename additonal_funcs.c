#include "shell.h"
/**
 * _getenv - function that searches  the environment list to
  * find the environment variable name, and returns a pointer to
  * the corresponding value string.
 * @name: the environment variable name.
 * Return: a pointer to the corresponding value string.
 */
char *_getenv(const char *name)
{
	char **env;
	int len = _strlen(name);

	for (env = environ; *env != NULL; ++env)
	{
		if (_strncmp(*env, name, len) == 0)
			return (&(*env)[len + 1]);
	}
	return (NULL);
}

/**
 * _itoa - function that converts an int to a string pointed to by str.
 * @str: The converted value.
 * @num: the number to convert.
 */
void _itoa(int num, char *str)
{
	int i, j;
	char tmp;

	for (i = 0; num != 0; i++)
	{
		str[i] = '0' + (num % 10);
		num /= 10;
	}
	for (j = 0; j < i / 2; j++)
	{
		tmp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = tmp;
	}
	str[i] = '\0';
}

/**
 * _getline - function that read from stdin.
 * @lineptr: the pointer where storing the buffer containing the text.
 * @n: the buffer size.
 * @stream: where funvtion reads the line from.
 * Return: On success,return the number of characters read.
 * return -1 on failure.
 */
int _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char *line;
	int bytes_read;
	int fd;

	if (stream == stdin)
		fd = STDIN_FILENO;
	else
		return (-1);
	if (lineptr == NULL || n == NULL)
		return (-1);

	line = malloc(BUFFER_SIZE);
	if (line == NULL)
		return (-1);

	bytes_read = read(fd, line, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(line);
		return (-1);
	}

	*lineptr = malloc(bytes_read);
	if (lineptr == NULL)
	{
		free(line);
		return (-1);
	}
	*lineptr[bytes_read] = '\n';

	_strcpy(*lineptr, line);
	return (0);
}

/**
 * delim_search - compare a character from str to
  * avaliable delimiters in delim.
 * @c: chararcter from str.
 * @delim: all delimiters.
 * Return: 1 if its found. and 0 if didn't found it.
 */
unsigned int delim_search(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - function that breaks a string into a sequence of zero or
 * more nonempty tokens.
 * @str: the string to be parsed
 * @delim: argument specifies a set of bytes that delimit the tokens
 * in the parsed string.
 * Return: The strtok() functions return a pointer to the next token,
 * or NULL if there are no more tokens.
 */
char *_strtok(char *str, char *delim)
{
	static char *old_str;
	char *portion;

	if (str == NULL)
		str = old_str;

	if (str == NULL)
		return (NULL);

	while (1)
	{
		if (delim_search(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	portion = str;

	while (1)
	{
		if (*str == '\0')
		{
			old_str = str;
			return (portion);
		}
		if (delim_search(*str, delim))
		{
			*str = '\0';
			old_str = str + 1;
			return (portion);
		}
		str++;
	}
}
