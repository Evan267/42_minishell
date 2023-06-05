/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvar_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:24:05 by agallet           #+#    #+#             */
/*   Updated: 2023/05/29 12:34:15 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	nbsame_env_var(char **var, char **env)
{
	int	i;
	int	j;
	int	k;
	int	same;

	i = 0;
	same = 0;
	while (env[i])
	{
		j = 0;
		while (var[j])
		{
			k = 0;
			while (var[j][k] && var[j][k] != '=')
				k++;
			if (ft_strnstr(env[i], var[j], ft_strlen(var[j])))
				same++;
			j++;
		}
		i++;
	}
	return (same);
}

static	void	completed_env(char **new_env, char **var, int *tab)
{
	while (var[tab[1]])
	{
		if (ft_strncmp(var[tab[1]], "1", 1))
			new_env[tab[3]] = ft_strdup(var[tab[1]]);
		tab[3] = tab[3] + 1;
		tab[1] = tab[1] + 1;
	}
	new_env[tab[3]] = NULL;
}

static	void	refresh_index(int *tab)
{
	tab[2] = 0;
	tab[1] = 0;
	tab[0] = tab[0] + 1;
	tab[3] = tab[3] + 1;
}

static	void	set_env(char **var, char **env, char **new_env, int *tab)
{
	if (var[tab[1]] && !ft_strncmp(env[tab[0]], var[tab[1]], tab[2]))
	{
		new_env[tab[3]] = ft_strdup(var[tab[1]]);
		free(var[tab[1]]);
		var[tab[1]] = ft_strdup("1");
	}
	else
		new_env[tab[3]] = env[tab[0]];
}

char	**new_env(char **var, char **env)
{
	char	**new_env;
	int		tab[4];
	int		length;

	ft_bzero(tab, 4 * sizeof(int));
	length = ft_strlen2d(env) + ft_strlen2d(var) - nbsame_env_var(var, env);
	new_env = malloc(sizeof(char *) * (length + 2));
	if (!new_env)
		return (NULL);
	while (tab[0] < ft_strlen2d(env))
	{
		while (env[tab[0]][tab[2]] && env[tab[0]][tab[2]++] != '=');
		while (var[tab[1]] && ft_strncmp(env[tab[0]], var[tab[1]], tab[2]))
			tab[1] = tab[1] + 1;
		set_env(var, env, new_env, tab);
		refresh_index(tab);
	}
	completed_env(new_env, var, tab);
	return (new_env);
}
