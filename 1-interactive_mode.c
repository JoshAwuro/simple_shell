#include "shell.h"
/**
 * signal_handler - function that terminal signals.
 * @signal_num: signal number.
 */
void signal_handler(int signal_num)
{
	(void)signal_num;
	write(STDOUT_FILENO, "\n", 2);
	write(STDOUT_FILENO, "$ ", 1);
}
/**
 * interactive_mode - the program in interactive mode.
 */
void interactive_mode(void)
{
	char *line;
	char **cmds;
	int err_check = 0;
	int running = 1;

	signal(SIGINT, signal_handler);
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 1);
		line = read_stdin();
		if (line != NULL)
		{
			cmds = tokeniz(line);
			err_check = excutcmd(cmds);
			if (err_check > 0)
			{
				error(err_check, cmds, running);
			}
			free(line);
			free(cmds);
		}
		running++;
	}
	free(line);
}
