/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:23:09 by agallet           #+#    #+#             */
/*   Updated: 2023/06/14 15:12:24 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(int argc, char **argv, char ***env)
{
	char	*path;
	char	*home;
	char	**new_var;
	int	i;

	i = 0;
	path = NULL;
	new_var = malloc(sizeof(char*) * 2);
	if (argc == 1)
	{
		home = getvaluevar("HOME", *env);
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
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
			return (1);
		}
	}
	path = getcwd(path, 0);
	new_var[0] = ft_strjoin("PWD=", path);
	new_var[1] = NULL;
	free(path);
	*env = new_env(&new_var, *env);
	ft_clear2d(new_var);
	return (0);
}
