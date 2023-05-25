#include "shell.h"
/**
 * program - function that look for the program name.
 * Return: the program name in success, and NULL if it fails.
 */
char *program(void)
{
	char *progname = NULL;
	char buffer[BUFFER_SIZE], pid[MAX_NUM], procpath[MAX_LENGHT] = "/proc/";
	int fp;

	_itoa(getpid(), pid);
	_strcat(procpath, pid);
	_strcat(procpath, "/cmdline");

	fp = open(procpath, O_RDONLY);
	if (fp != -1)
	{
		int nb = read(fp, buffer, sizeof(progname));

		if (nb != -1)
		{
			progname = malloc(nb * sizeof(char) + 1);
			strncpy(progname, buffer, nb);
			progname[nb] = '\0';
			close(fp);
			return (progname);
		}
		close(fp);
	}
	return (NULL);
}

/**
 * error - function that handle the commands errors.
 * @status: status value.
 * @s: the command.
 * @running: the number of command been running.
 * Description: the status value define the error should prompt
   * 1: command errors (command not found...)
   * 2:	exit errors (illegal number...)
 */
void error(int status, char **s, int running)
{
	char *progname = program();
	char errun[MAX_NUM];

	_itoa(running, errun);
	write(STDOUT_FILENO, progname, _strlen(progname));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, errun, _strlen(errun));
	write(STDOUT_FILENO, ": ", 2);

	if (status == 1)
	{
		perror(*s);
	}
	else if (status == 2)
	{
		char exit_err[] = "exit: Illegal number: ";

		write(STDOUT_FILENO, exit_err, _strlen(exit_err));
		write(STDOUT_FILENO, s[1], _strlen(s[1]));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(progname);

}
