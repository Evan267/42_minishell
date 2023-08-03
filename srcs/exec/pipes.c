/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:05:38 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:24:43 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	**malloc_pipes(int len_cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * len_cmds - 1);
	if (!pipes)
		return (NULL);
	while (i < len_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int *) * 2);
		if (!pipes[i])
		{
			stop_pipes(pipes, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	**create_pipes(int len_cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	if (len_cmds > 1)
	{
		pipes = malloc_pipes(len_cmds);
		if (!pipes)
			return (ft_putendl_fd("Erreur de malloc", 2), NULL);
		while (i < len_cmds - 1)
		{
			if (pipe(pipes[i]) == -1)
			{
				perror("minishell");
				return (NULL);
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
