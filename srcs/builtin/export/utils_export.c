/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:53:22 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 13:33:02 by eberger          ###   ########.fr       */
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
			if (ft_strncmp(env[i], var[j], lgst_wrd(env[i], var[j])))
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
