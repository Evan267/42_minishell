/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:56:27 by eberger           #+#    #+#             */
/*   Updated: 2023/06/09 11:46:33 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_infile_outfile(int in, int out)
{
	if (in && in > 1)
	{
		if (close(in) == -1)
			perror("close");
	}
	if (out && out > 1)
	{
		if (close(out) == -1)
			perror("close");
	}
}

static void	delete_infile(char **split, int i)
{
	if (!ft_strncmp(split[i], "<<", 2))
	{
		if (ft_strlen(split[i]) == 2)
			split[i + 1] = empty_str(split[i + 1]);
		split[i] = empty_str(split[i]);
	}
	else if (!ft_strncmp(split[i], "<", 1))
	{
		if (ft_strlen(split[i]) == 1)
			split[i + 1] = empty_str(split[i + 1]);
		split[i] = empty_str(split[i]);
	}
}

static void	delete_outfile(char **split, int i)
{
	if (!ft_strncmp(split[i], ">>", 2))
	{
		if (ft_strlen(split[i]) == 2)
			split[i + 1] = empty_str(split[i + 1]);
		split[i] = empty_str(split[i]);
	}
	else if (!ft_strncmp(split[i], ">", 1))
	{
		if (ft_strlen(split[i]) == 1)
			split[i + 1] = empty_str(split[i + 1]);
		split[i] = empty_str(split[i]);
	}
}

char	*delete_infile_outfile(char **split)
{
	int		i;
	char	*ret;

	i = 0;
	while (split[i])
	{
		delete_infile(split, i);
		delete_outfile(split, i);
		i++;
	}
	ret = ft_joinsplit(split);
	return (ret);
}

void	error_open(char *file, int fd, int must_exit)
{
	char	*error_head;

	if (fd == -1)
	{
		error_head = ft_strjoin("minishell: ", file);
		perror(error_head);
		free(error_head);
		if (must_exit)
			exit(1);
	}
}
