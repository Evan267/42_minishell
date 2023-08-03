/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvar_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:24:05 by agallet           #+#    #+#             */
/*   Updated: 2023/08/03 09:29:48 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static	void	set_env(char ***vr, char **env, char **new_env, int *tab)
{
	int	i;
	int	j;

	i = tab[0];
	j = tab[1];
	if ((*vr)[j]
		&& !ft_strncmp(env[i], (*vr)[j], lgst_wrd(env[i], (*vr)[j]))
		&& (*vr)[j][fund_equal((*vr)[j])] == '=')
	{
		new_env[tab[3]] = ft_strdup((*vr)[j]);
		*vr = del_var(*vr, j);
	}
	else
		new_env[tab[3]] = ft_strdup(env[i]);
	if ((*vr)[j]
			&& !ft_strncmp(env[i], (*vr)[j], lgst_wrd(env[i], (*vr)[j]))
			&& (*vr)[i][fund_equal((*vr)[j])] != '=')
		*vr = del_var(*vr, tab[1]);
}

char	**new_env(char ***var, char **env)
{
	char	**new_env;
	int		tab[5];
	int		length;
	int		longest;

	ft_bzero(tab, 5 * sizeof(int));
	tab[4] = nbdiff_env_var(*var, env);
	length = ft_strlen2d(env) + tab[4];
	new_env = malloc(sizeof(char *) * (length + 1));
	if (!new_env)
		return (NULL);
	while (tab[0] < ft_strlen2d(env))
	{
		if ((*var)[tab[1]])
			longest = lgst_wrd(env[tab[0]], (*var)[tab[1]]);
		while ((*var)[tab[1]]
				&& ft_strncmp((*var)[tab[1]], env[tab[0]], longest))
			tab[1] = tab[1] + 1;
		set_env(var, env, new_env, tab);
		refresh_index(tab);
	}
	completed_env(new_env, (*var), tab);
	ft_clear2d(env);
	return (new_env);
}
