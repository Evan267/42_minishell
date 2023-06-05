/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:06:22 by agallet           #+#    #+#             */
/*   Updated: 2023/05/29 11:40:26 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* parse export */

static	int	fund_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static	int	i_samevar(int i1, int i2, char **var)
{
	int	nb1;
	int	nb2;

	nb1 = fund_equal(var[i1]);
	nb2 = fund_equal(var[i2]);
	if (i1 > i2 && var[nb1][nb1])
		return (i2);
	else if (i1 < i2 && var[i2][nb2])
		return (i1);
	else if (!var[i2][nb2])
		return (i2);
	else if (!var[i1][nb1])
		return (i1);
	else
		return (i1);
}

char	**same_var(char **var)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	while (var[i])
	{
		while (var[j])
		{
			length = fund_equal(var[j]);
			if (!ft_strncmp(var[i], var[j], length) && i != j)
			{
				var = del_var(var, i_samevar(i, j, var));
				break ;
			}
			j++;
		}
		i++;
	}
	return (var);
}

char	**parse_var(char **str)
{
	char	**var;
	int		i;
	int		iv;

	i = 0;
	iv = 0;
	while (str[i] && !ft_strnstr(str[i], "export", 6))
		i++;
	var = malloc(sizeof(char *) * (ft_strlen2d(str) - i));
	while (str[++i])
	{
		var[iv] = ft_strdup(str[i]);
		iv++;
	}
	var[iv] = NULL;
	return (var);
}


