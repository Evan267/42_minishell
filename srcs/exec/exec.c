/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/06/13 15:25:30 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *cmd, char ***env)
{
	char	*path;
	char	**args;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	path = ft_path(args, getenv("PATH"));
	if (execve(path, args, *env) == -1)
	{
		perror("execve");
		exit(127);
	}
}

void	exec_builtins_fork(char *cmd, char ***env, int whichBuiltins, int *in_out)
{
	char	**args;
	int		status;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	status = builtins(args, env, whichBuiltins, in_out);
	ft_clear2d(args);
	exit(status);
}

int	exec_builtins(char *cmd, char ***env, int whichBuiltins, int *in_out)
{
	char	**args;
	int		status;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	status = builtins(args, env, whichBuiltins, in_out);
	ft_clear2d(args);
	return (status);
}
