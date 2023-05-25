#include "shell.h"
/**
 * main - run the program.
 * Return: 0 always.
 */
int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		interactive_mode();
	}
	else
	{
		non_interactive_mode();
	}
	return (0);
}
