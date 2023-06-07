/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:27:26 by eberger           #+#    #+#             */
/*   Updated: 2023/06/06 15:35:32 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	test_builtins(char *cmds)
{
	char	**split;
	char	*cmd_without_io;

	split = ft_split_cmds(cmds, ' ');
	split = ft_trim_builtins(split);
	cmd_without_io = delete_infile_outfile(split);
	split = ft_split_cmds(cmd_without_io, ' ');
	if (!ft_strncmp(split[0], "echo", ft_strlen("echo") + 1))
		return (ft_clear2d(split), 1);
	else if (!ft_strncmp(split[0], "cd", ft_strlen("cd") + 1))
		return (ft_clear2d(split), 2);
	else if (!ft_strncmp(split[0], "pwd", ft_strlen("pwd") + 1))
		return (ft_clear2d(split), 3);
	else if (!ft_strncmp(split[0], "export", ft_strlen("export") + 1))
		return (ft_clear2d(split), 4);
	else if (!ft_strncmp(split[0], "unset", ft_strlen("unset") + 1))
		return (ft_clear2d(split), 5);
	else if (!ft_strncmp(split[0], "env", ft_strlen("env") + 1))
		return (ft_clear2d(split), 6);
	else if (!ft_strncmp(split[0], "exit", ft_strlen("exit") + 1))
		return (ft_clear2d(split), 7);
	return (ft_clear2d(split), 0);
}

int	builtins(char **args, char ***env, int builtin, int *in_out)
{
	int	nb_args;

	nb_args = ft_strlen2d(args);
	if (builtin == 1)
		return (ft_echo(nb_args, args));
	else if (builtin == 2)
		return (ft_cd(nb_args, args, env));
	else if (builtin == 3)
		return (ft_pwd(nb_args, args));
	else if (builtin == 4)
		return (ft_export(nb_args, args, env));
	else if (builtin == 5)
		return (ft_unset(nb_args, args, env));
	else if (builtin == 6)
		return (ft_env(nb_args, args, env));
	else if (builtin == 7)
		return (ft_exit(nb_args, args, env, in_out));
	return (-1);
}
