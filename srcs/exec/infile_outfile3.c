/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:02:28 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:23:54 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*error_infile_outfile(int *status, char **split, char *cmd)
{
	perror("minishell");
	*status = 1;
	ft_clear2d(split);
	free(cmd);
	return (NULL);
}

char	*infile_outfile(char *cmd, int *in_out, int *status, char ***env)
{
	char	**split;
	char	*ret;
	int		j;

	j = 0;
	in_out[0] = 0;
	in_out[1] = 0;
	split = ft_split_cmds(cmd, ' ');
	while (split[j])
	{
		infile(split + j, in_out, *status, env);
		outfile(split, j, in_out);
		j++;
	}
	if (in_out[1] == -1 || in_out[0] == -1)
		return (error_infile_outfile(status, split, cmd));
	free(cmd);
	ret = delete_infile_outfile(split);
	ft_clear2d(split);
	return (ret);
}

void	after_fork(int *in_out, int **pipes, int *i)
{
	dup_cond(in_out, i, pipes);
	close_infile_outfile(in_out, in_out + 1);
}
