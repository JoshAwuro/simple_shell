#include "main.h"

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int pdx = 2;

	asm("mov %1, %0\n\t""add $3, %0"
			: "=r" (pdx)
			: "r" (pdx));

	if (ac == 2)
	{
		pdx = open(av[1], O_RDONLY);
		if (pdx == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ac[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputs('\n');
				_eputs(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info=>readpdx = pdx;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
