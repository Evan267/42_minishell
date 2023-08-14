/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/08/14 12:30:06 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_execve(struct stat info, char *path)
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
	perror("minishell");
	if (access(path, F_OK))
		exit(127);
	exit(126);
}

void	exec(char *cmd, char ***env)
{
	char		*path;
	char		**args;
	char		*path_env;
	struct stat	info;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	if ((ft_strchr(args[0], '/')))
		path = args[0];
	else
	{
		path_env = getvaluevar("PATH", *env);
		path = ft_path(args, path_env);
		free(path_env);
	}
	stat(path, &info);
	if (execve(path, args, *env) == -1)
		error_execve(info, path);
}

void	exec_builtins_fork(char *cmd, char ***env, int btin, int *in_out)
{
	char	**args;
	int		status;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	status = builtins(args, env, btin, in_out);
	ft_clear2d(args);
	exit(status);
}

int	exec_builtins(char *cmd, char ***env, int whichBuiltin, int *in_out)
{
	char	**args;
	int		status;

	args = ft_split_cmds(cmd, ' ');
	args = ft_trim_builtins(args);
	status = builtins(args, env, whichBuiltin, in_out);
	ft_clear2d(args);
	return (status);
}
