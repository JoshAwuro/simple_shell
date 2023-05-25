#include "shell.h"
/**
 * _strdup - function that returns a pointer to a newly allocated space
 * in memory, which contains a copy of the string given as a parameter.
 * @str: string given as a parameter.
 * Return: NULL if str = NULL and On success returns a pointer to
 * the duplicated string. It returns NULL if insufficient memory was available
 */
char *_strdup(char *str)
{
	char *newstr;
	int len;
	int i;


	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		len = strlen(str);
		newstr = malloc((sizeof(char) * len) + 1);
		if (newstr == NULL)
		{
			free(newstr);
			return (NULL);
		}
		for (i = 0; i < len; i++)
			newstr[i] = str[i];
		newstr[len] = '\0';
	}
	return  (newstr);
}

/**
 * _strlen - function that returns the length of a string.
 * @s: string.
 * Return: length of a string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * _strncmp - function that compares two strings tell a specific index.
 * @str1: first string
 * @str2: second string
 * @n: index
 * Return: return 0 if strings are equal, and -1 if its not.
 */
int _strncmp(const char *str1, const char *str2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] == str2[i])
		{
			continue;
		}
		else
		{
			return (-1);
		}
	}
	return (0);
}
/**
 * _strcat - function appends the src string to the dest string
 * @dest: first string
 * @src: second string
 * Return: a pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int r = _strlen(dest);

	while (*(src + i) != '\0')
	{
		*(dest + (r + i)) = *(src + i);
		i++;
	}
	*(dest + (r + i)) = '\0';
	return (dest);
}
/**
 * *_strcpy -  copies the string pointed to by src including the
 * terminating null byte (\0), to the buffer pointed to by dest.
 * @dest: copy to
 * @src: copy from
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = -1;

	do {
		i++;
		*(dest + i) = *(src + i);
	} while (*(src + i) != '\0');
	return (dest);
}
