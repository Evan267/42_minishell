#include "minishell.h"

void	ctrl_d(char *prompt, char **envp, int sw)
{
	if (sw)
	{
		tputs("\033[1A", 1, putchar);
		printf("%s exit\n", prompt);
		free(prompt);
		ft_clear2d(envp);
	}
	exit(0);
}
