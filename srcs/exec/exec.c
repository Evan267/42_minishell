/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/06/08 14:16:31 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *cmd, char ***env)
{
	char	*path;
	char	**args;

	*env = NULL;
	args = ft_split_cmd(cmd, ' ');
	args[0] = delete_quote(args[0], '\'');
	args[0] = delete_quote(args[0], '\"');
	path = ft_path(args, getenv("PATH"));
	if (execve(path, args, *env) == -1)
	{
		perror("execve");
		exit(127);
	}
}

int	exec_builtins(char *cmd, char ***env, int whichBuiltins, int *in_out)
{
	char	**args;
	int		status;

	args = ft_split_cmd(cmd, ' ');
	args = ft_trim_builtins(args);
	status = builtins(args, env, whichBuiltins, in_out);
	ft_clear2d(args);
	return (status);
}
