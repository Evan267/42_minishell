/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:23:09 by agallet           #+#    #+#             */
/*   Updated: 2023/06/19 10:00:00 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	old_pwd(char ***env)
{
	char	*old_pwd;
	char	**change_var;

	change_var = malloc(sizeof(char*) * 2);
	if (!change_var)
		return ;
	old_pwd = getvaluevar("PWD", *env);
	change_var[0] = ft_strjoin("OLDPWD=", old_pwd);
	change_var[1] = NULL;
	free(old_pwd);
	*env = new_env(&change_var, *env);
	ft_clear2d(change_var);
}

int	ft_cd(int argc, char **argv, char ***env)
{
	char	*path;
	char	*home;
	char	**new_var;

	path = NULL;
	new_var = malloc(sizeof(char*) * 2);
	if (!new_var)
		return (1);
	if (argc == 1)
	{
		home = getvaluevar("HOME", *env);
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			free(new_var);
			return (1);
		}
		chdir(home);
		free(home);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			perror("minishell: cd:");
			free(new_var);
			return (1);
		}
	}
	old_pwd(env);
	path = getcwd(path, 0);
	new_var[0] = ft_strjoin("PWD=", path);
	new_var[1] = NULL;
	free(path);
	*env = new_env(&new_var, *env);
	ft_clear2d(new_var);
	return (0);
}
