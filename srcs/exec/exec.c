/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 11:27:07 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *cmd, char ***env)
{
	char	*path;
	char	**args;
	char	*path_env;
	struct	stat	info;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	if (!access(args[0], X_OK) && args[0][0] == '.' && args[0][1] == '/')
		path = args[0];
	else
	{
		path_env = getvaluevar("PATH", *env);
		path = ft_path(args, path_env);	
		free(path_env);
	}
	stat(path, &info);
	if (execve(path, args, *env) == -1)
	{
		if (S_ISDIR(info.st_mode))
		{
			if ((path[0] == '.' || path[0] == '/'))
			{
				ft_putendl_fd("minishell: is a directory", 2);
				exit (126);
			}
			else
				command_not_found(path);
		}
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
