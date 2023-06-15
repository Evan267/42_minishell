/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:45 by eberger           #+#    #+#             */
/*   Updated: 2023/06/15 12:05:23 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void gestionnaire_sigint(int signum)
{
    (void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

void    set_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	rl_catch_signals = 0;
    if (isatty(fileno(stdin)))
	{
        sa_int.sa_handler = gestionnaire_sigint;
        sigemptyset(&sa_int.sa_mask);
        sa_int.sa_flags = 0;

        sa_quit.sa_handler = SIG_IGN;
        sigemptyset(&sa_quit.sa_mask);
        sa_quit.sa_flags = 0;

        // Enregistrement du gestionnaire de signal
        if (sigaction(SIGINT, &sa_int, NULL) == -1) {
            printf("Erreur lors de l'enregistrement du gestionnaire de signal");
        }
		if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			printf("Erreur lors de l'enregistrement du gestionnaire de signal");
    }
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
	//printf("%d / %d", info->si_pid, pid);
	while(pid != -1)
	{
		pid = wait(NULL);
	}
	if (main_pid == info->si_pid)
		printf("\n");
}

void	exit_sig(void)
{
	struct	sigaction	sa_int;

	if (isatty(fileno(stdin)))
	{
		sa_int.sa_sigaction = exit_sigint;
		sigemptyset(&sa_int.sa_mask);
		sa_int.sa_flags = 0;
		if (sigaction(SIGINT, &sa_int, NULL) == -1)
		{
			perror("Erreur lors de l'appel à sigaction");
			return ;
		}
	}
}

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


void	pipe_sig(int sig)
{
	int	pid;
	(void) sig;
	pid = wait(NULL);
	setstop(1);
	if (pid == -1)
	{
		printf("\n");
		exit(1);
	}
}

void	pipe_sigint(void)
{
	struct	sigaction	sa_int;

	if (isatty(fileno(stdin)))
	{
		sa_int.sa_handler = pipe_sig;
		sigemptyset(&sa_int.sa_mask);
		sa_int.sa_flags = 0;

		if (sigaction(SIGINT, &sa_int, NULL) == -1)
		{
			perror("Erreur lors de l'appel à sigaction");
			return ;
		}
	}
}
