/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:14:23 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 13:47:05 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	saved_dup(int *in_out)
{
	in_out[2] = dup(STDIN_FILENO);
	in_out[3] = dup(STDOUT_FILENO);
}

void	dup_in_out(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		exit(0);
	if (dup2(out, STDOUT_FILENO) == -1)
		exit(0);
}

void	dup_cond(int *in_out, int *i, int **pipes)
{
	int	in;
	int	out;

	in = 0;
	out = 1;
	if (!(i[0] == 0 && i[0] == i[1] - 1))
	{
		if (i[0] == 0)
			out = pipes[i[0]][1];
		else if (i[0] == i[1] - 1)
			in = pipes[i[0] - 1][0];
		else if (i[0] > 0 && i[0] < i[1] - 1)
		{
			in = pipes[i[0] - 1][0];
			out = pipes[i[0]][1];
		}
	}
	if (in_out[0] > 0)
		in = in_out[0];
	if (in_out[1] > 1)
		out = in_out[1];
	dup_in_out(in, out);
}
