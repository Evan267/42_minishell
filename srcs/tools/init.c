/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:17 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:15:15 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(char **env)
{
	char	**envp;
	char	**var;
	char	*str_shlvl;
	int		value_shlvl;

	value_shlvl = 0;
	var = malloc(sizeof(char *) * 2);
	envp = ft_strdup2d(env);
	str_shlvl = getvaluevar("SHLVL", envp);
	if (str_shlvl)
		value_shlvl = ft_atoi(str_shlvl);
	value_shlvl++;
	free(str_shlvl);
	str_shlvl = ft_itoa(value_shlvl);
	var[0] = ft_strjoin("SHLVL=", str_shlvl);
	var[1] = NULL;
	free(str_shlvl);
	envp = new_env(&var, envp);
	ft_clear2d(var);
	return (envp);
}

void	unset_(char ***envp)
{
	char	**str;

	str = malloc(sizeof(char *) * 4);
	str[0] = ft_strdup("unset");
	str[1] = ft_strdup("_");
	str[2] = ft_strdup("OLDPWD");
	str[3] = NULL;
	ft_unset(3, str, envp);
	ft_clear2d(str);
}

void	setoldpwd(char ***envp)
{
	char	**str;

	str = malloc(sizeof(char *) * 3);
	str[0] = ft_strdup("export");
	str[1] = ft_strdup("OLDPWD");
	str[2] = NULL;
	ft_export(2, str, envp);
	ft_clear2d(str);
}

void	set_shell(int sw)
{
	static struct termios	term;

	if (sw)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	**init(char **line, char **env, char **history_path, int *status)
{
	char	**envp;

	*line = NULL;
	*history_path = NULL;
	*status = 0;
	envp = create_env(env);
	unset_(&envp);
	setoldpwd(&envp);
	reload_history(history_path, envp);
	set_shell(1);
	return (envp);
}
