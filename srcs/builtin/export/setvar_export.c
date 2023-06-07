/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvar_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:24:05 by agallet           #+#    #+#             */
/*   Updated: 2023/06/07 13:41:41 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	nbdiff_env_var(char **var, char **env)
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
			if (ft_strncmp(env[i], var[j], longest_word(env[i], var[j])))
				same++;
			j++;
		}
		i++;
	}
	return (same / ft_strlen2d(env));
}

int	nbsame_env_var(char **var, char **env)
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
			if (!ft_strncmp(env[i], var[j], k + 1))
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
		if (ft_strncmp(var[tab[1]], "128", 3))
		{
			new_env[tab[3]] = ft_strdup(var[tab[1]]);
			tab[3] = tab[3] + 1;
		}
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

static	void	set_env(char ***var, char **env, char **new_env, int *tab)
{
	if ((*var)[tab[1]] && !ft_strncmp(env[tab[0]], (*var)[tab[1]], longest_word(env[tab[0]], (*var)[tab[1]])) && (*var)[tab[1]][fund_equal((*var)[tab[1]])] == '=')
	{
		new_env[tab[3]] = ft_strdup((*var)[tab[1]]);
		*var = del_var(*var, tab[1]);
	}
	else
		new_env[tab[3]] = ft_strdup(env[tab[0]]);
	if ((*var)[tab[1]] && !ft_strncmp(env[tab[0]], (*var)[tab[1]], longest_word(env[tab[0]], (*var)[tab[1]])) && (*var)[tab[1]][fund_equal((*var)[tab[1]])] != '=')
		*var = del_var(*var, tab[1]);
}

char	**new_env(char ***var, char **env)
{
	char	**new_env;
	int		tab[5];
	int		length;

	ft_bzero(tab, 5 * sizeof(int));	
	tab[4] = nbdiff_env_var(*var, env);
	length = ft_strlen2d(env) + tab[4];
	new_env = malloc(sizeof(char *) * (length + 1));
	if (!new_env)
		return (NULL);
	while (tab[0] < ft_strlen2d(env))
	{
		while ((*var)[tab[1]] && ft_strncmp((*var)[tab[1]], env[tab[0]], longest_word(env[tab[0]], (*var)[tab[1]])))
			tab[1] = tab[1] + 1;
		set_env(var, env, new_env, tab);
		refresh_index(tab);
	}
	completed_env(new_env, (*var), tab);
	return (new_env);
}
