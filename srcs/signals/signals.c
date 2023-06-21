/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:45 by eberger           #+#    #+#             */
/*   Updated: 2023/06/21 09:41:52 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gestionnaire_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	rl_catch_signals = 0;
	if (isatty(fileno(stdin)))
	{
		sa_int.sa_handler = gestionnaire_sigint;
		sigemptyset(&sa_int.sa_mask);
		sa_int.sa_flags = 0;
		sa_quit.sa_handler = SIG_IGN;
		sigemptyset(&sa_quit.sa_mask);
		sa_quit.sa_flags = 0;
		if (sigaction(SIGINT, &sa_int, NULL) == -1)
			printf("Erreur lors de l'enregistrement du gestionnaire de signal");
		if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			printf("Erreur lors de l'enregistrement du gestionnaire de signal");
	}
}

void	exit_sig(void)
{
	struct sigaction	sa_int;	
	struct sigaction	sa_quit;

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
		sa_quit.sa_sigaction = exit_sigint;
		sigemptyset(&sa_quit.sa_mask);
		sa_quit.sa_flags = 0;
		if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			printf("Erreur lors de l'enregistrement du gestionnaire de signal");
	}
}

void	pipe_sig(int sig)
{
	int	pid;

	(void)sig;
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
	struct sigaction	sa_int;

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
