/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:25:14 by eberger           #+#    #+#             */
/*   Updated: 2023/06/16 14:11:10 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_here_doc(int *pipes, char *limiter, int status, char ***env)
{
	char	*tmp;

	close(pipes[0]);
	tmp = readline("> ");
	if (!tmp)
		ctrl_d(NULL, NULL, 0);
	while (ft_strncmp(limiter, tmp, ft_strlen(tmp))
		|| ft_strlen(limiter) > ft_strlen(tmp))
	{
		tmp = replace_env_var(tmp, status, env);
		ft_putendl_fd(tmp, pipes[1]);
		free(tmp);
		tmp = readline("> ");
	}
	free(tmp);
	exit(0);
}

int	here_doc(char *limiter, int status, char ***env)
{
	int		pipes[2];
	pid_t	pid;
	int		status_wait;

	if (pipe(pipes) == -1)
	{	
		perror("pipe");
		exit(127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pipe");
		exit(127);
	}
	else if (pid == 0)
	{
		heredoc_sigint();
		child_here_doc(pipes, limiter, status, env);
	}
	waitpid(pid, &status_wait, 0);
	close(pipes[1]);
	return (pipes[0]);
}
