/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:46 by eberger           #+#    #+#             */
/*   Updated: 2023/06/15 13:23:30 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *file_or_limiter, int is_heredoc, int *status)
{
	int	ret;

	ret = 0;
	file_or_limiter = delete_quote(file_or_limiter, '\"');
	file_or_limiter = delete_quote(file_or_limiter, '\'');
	if (file_or_limiter && !is_heredoc)
	{
		ret = open(file_or_limiter, O_RDONLY, 0);
		if (ret == -1)
		{
			error_open(file_or_limiter, ret, 0);
			*status = 1;
			if (file_or_limiter)
				free(file_or_limiter);
			return (-1);
		}
	}
	else if (file_or_limiter && is_heredoc)
	{
		ret = here_doc(file_or_limiter, status);
	}
	if (file_or_limiter)
		free(file_or_limiter);
	return (ret);
}

int	open_outfile(char *file, int append)
{
	int	ret;

	ret = 0;
	file = delete_quote(file, '\"');
	file = delete_quote(file, '\'');
	if (file && append)
		ret = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ret == -1)
		perror("open");
	if (file)
		free(file);
	return (ret);
}

void	infile(char **split, int i, int *in_out, int *status)
{
	char	*file;

	file = NULL;
	if (!ft_strncmp(split[i], "<<", 2))
	{
		if (in_out[0])
			close(in_out[0]);
		if (ft_strlen(split[i]) > 2)
			file = ft_strdup(split[i] + 2);
		else
			file = ft_strdup(split[i + 1]);
		in_out[0] = open_infile(file, 1, status);
	}
	else if (!ft_strncmp(split[i], "<", 1))
	{
		if (in_out[0])
			close(in_out[0]);
		if (ft_strlen(split[i]) > 1)
			file = ft_strdup(split[i] + 1);
		else
			file = ft_strdup(split[i + 1]);
		in_out[0] = open_infile(file, 0, status);
	}
}

void	outfile(char **split, int i, int *in_out)
{
	char	*file;

	file = NULL;
	if (!ft_strncmp(split[i], ">>", 2))
	{
		if (in_out[1])
			close(in_out[1]);
		if (ft_strlen(split[i]) > 2)
			file = ft_strdup(split[i] + 2);
		else
			file = ft_strdup(split[i + 1]);
		in_out[1] = open_outfile(file, 1);
	}
	else if (!ft_strncmp(split[i], ">", 1))
	{
		if (in_out[1])
			close(in_out[1]);
		if (ft_strlen(split[i]) > 1)
			file = ft_strdup(split[i] + 1);
		else
			file = ft_strdup(split[i + 1]);
		in_out[1] = open_outfile(file, 0);
	}
}

char	*infile_outfile(char *cmd, int *in_out, int *status)
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
		infile(split, j, in_out, status);
		outfile(split, j, in_out);
		if (in_out[1] == -1 || *status == 1)
			return (NULL);
		j++;
	}
	ret = delete_infile_outfile(split);
	ft_clear2d(split);
	free(cmd);
	return (ret);
}

void	after_fork(int *in_out, int **pipes, int *i)
{
	dup_cond(in_out, i, pipes);
	close_infile_outfile(in_out[0], in_out[1]);
}
