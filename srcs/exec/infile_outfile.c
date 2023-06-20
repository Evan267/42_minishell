/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:46 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 14:34:50 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(char *file, int *in_out)
{
	int	ret;

	ret = 0;
	file = delete_quote(file, '\"');
	file = delete_quote(file, '\'');
	if (file && in_out[0] != -1 && in_out[1] != -1)
	{
		ret = open(file, O_RDONLY, 0);
		if (ret == -1)
		{
			in_out[0] = -1;
			if (file)
				free(file);
			return ;
		}
	}
	if (file)
		free(file);
	if (ret)
		in_out[0] = ret;
}

void	open_heredoc(char *limiter, int *in_out, int status, char ***env)
{
	int	ret;

	ret = 0;
	limiter = delete_quote(limiter, '\"');
	limiter = delete_quote(limiter, '\'');
	if (limiter)
		ret = here_doc(limiter, status, env);
	if (ret && (in_out[1] == -1 || in_out[0] == -1))
	{
		close(ret);
		ret = 0;
	}
	if (limiter)
		free(limiter);
	if (ret)
		in_out[0] = ret;
}

void	open_outfile(char *file, int append, int *in_out)
{
	int	ret;

	ret = 0;
	file = delete_quote(file, '\"');
	file = delete_quote(file, '\'');
	if (file && append && in_out[1] != -1 && in_out[0] != -1)
		ret = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file && in_out[1] != -1 && in_out[0] != -1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file)
		free(file);
	if (ret)
		in_out[1] = ret;
}

void	infile(char **split, int *in_out, int status, char ***env)
{
	char	*file;

	file = NULL;
	if (!ft_strncmp(*split, "<<", 2))
	{
		if (in_out[0] > 1)
			close(in_out[0]);
		if (ft_strlen(*split) > 2)
			file = ft_strdup(*split + 2);
		else
			file = ft_strdup(*(split + 1));
		open_heredoc(file, in_out, status, env);
	}
	else if (!ft_strncmp(*split, "<", 1))
	{
		if (in_out[0] > 1)
			close(in_out[0]);
		if (ft_strlen(*split) > 1)
			file = ft_strdup(*split + 1);
		else
			file = ft_strdup(*(split + 1));
		open_infile(file, in_out);
	}
}

void	outfile(char **split, int i, int *in_out)
{
	char	*file;

	file = NULL;
	if (!ft_strncmp(split[i], ">>", 2))
	{
		if (in_out[1] > 1)
			close(in_out[1]);
		if (ft_strlen(split[i]) > 2)
			file = ft_strdup(split[i] + 2);
		else
			file = ft_strdup(split[i + 1]);
		open_outfile(file, 1, in_out);
	}
	else if (!ft_strncmp(split[i], ">", 1))
	{
		if (in_out[1] > 1)
			close(in_out[1]);
		if (ft_strlen(split[i]) > 1)
			file = ft_strdup(split[i] + 1);
		else
			file = ft_strdup(split[i + 1]);
		open_outfile(file, 0, in_out);
	}
}
