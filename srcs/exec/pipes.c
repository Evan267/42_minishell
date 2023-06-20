/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:05:38 by eberger           #+#    #+#             */
/*   Updated: 2023/06/19 15:08:57 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(int **pipes, int len_cmds)
{
	int	i;

	i = 0;
	while (i < len_cmds - 1)
	{
		if (close(pipes[i][0]) == -1)
			perror("close");
		if (close(pipes[i][1]) == -1)
			perror("close");
		i++;
	}
}

int	**create_pipes(int len_cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	if (len_cmds > 1)
	{
		pipes = malloc(sizeof(int *) * len_cmds - 1);
		while (i < len_cmds - 1)
		{
			pipes[i] = malloc(sizeof(int) * 2);
			i++;
		}
		i = 0;
		while (i < len_cmds - 1)
		{
			if (pipe(pipes[i]) == -1)
			{
				perror("pipe");
				exit(127);
			}
			i++;
		}
		return (pipes);
	}
	else
		return (NULL);
}

void	stop_pipes(int **pipes, int len_cmds)
{
	int	i;

	i = 0;
	close_pipes(pipes, len_cmds);
	while (i < len_cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
