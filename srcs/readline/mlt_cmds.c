/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlt_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:25:42 by eberger           #+#    #+#             */
/*   Updated: 2023/06/22 10:51:32 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infos_cmd(int **pipes, int *info_cmds, int *in_out, int *i)
{
	if (info_cmds[0])
	{
		close_pipes(pipes, info_cmds[1]);
		close_infile_outfile(in_out, in_out + 1);
		exit(info_cmds[0]);
	}
	after_fork(in_out, pipes, i);
	close_pipes(pipes, info_cmds[1]);
}

void	init_cmds(int *i, int *info_cmds, int **pid)
{
	i[0] = 0;
	i[1] = info_cmds[1];
	*pid = malloc(sizeof(pid_t) * i[1]);
}

void	check_fork(int *pid, int *i)
{
	if (pid[i[0]] == -1)
	{
		perror("fork");
		exit(127);
	}
}

void	clear_exec(char **line, int *info_cmds, char **cmds)
{
	free(*line);
	while (info_cmds[1]--)
		free(cmds[info_cmds[1]]);
	free(cmds);
}

void	clear_prompt(char *second_part, char *first_part)
{
	free(second_part);
	second_part = NULL;
	free(first_part);
	first_part = NULL;
}
