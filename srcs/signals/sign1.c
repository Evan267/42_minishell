
#include "minishell.h"

void	heredoc_sig(int sig)
{
	(void) sig;
	exit(1);
}

void	heredoc_sigint(void)
{
	struct	sigaction	sa_int;

	if (isatty(fileno(stdin)))
	{
		sa_int.sa_handler = heredoc_sig;
		sigemptyset(&sa_int.sa_mask);
		sa_int.sa_flags = SA_RESTART;

		if (sigaction(SIGINT, &sa_int, NULL) == -1)
		{
			perror("Erreur lors de l'appel à sigaction");
			return ;
		}
	}
}

int	setstop(int nb)
{
	static	int	val;

	if (nb >= 0)
		val = nb;
	return (val);
}

int	getstop(void)
{
	return (setstop(-1));
}

void	exit_sigint(int	sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	pid_t	pid;
	static pid_t	main_pid;

	if (!main_pid)
		main_pid = info->si_pid;
	if (main_pid != info->si_pid)
	{
		tputs("\033[1A", 1, putchar);
		return ;
	}
	pid = wait(NULL);
	while(pid != -1)
	{
		pid = wait(NULL);
	}
	if (main_pid == info->si_pid && sig != SIGQUIT)
		printf("\n");
}
