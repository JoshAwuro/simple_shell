#include "shell.h"
/**
 * non_interactive_mode - the program in the non interactive mode.
 */
void non_interactive_mode(void)
{
	char *line;
	char **cmds;
	int err_check = 0;
	int running = 1;

	while (1)
	{
		line = read_stream();
		cmds = tokeniz(line);
		err_check = excutcmd(cmds);
		if (err_check > 0)
		{
			error(err_check, cmds, running);
		}
	}
	free(line);
	free(cmds);
}
