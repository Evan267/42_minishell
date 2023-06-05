/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:03:21 by agallet           #+#    #+#             */
/*   Updated: 2023/05/29 12:26:26 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check export */

static	int	put_errors(char *str)
{
	printf("bash: export: `%s\n': not a valid identifier", str);
	return (1);
}

int	laws_env(char *var)
{
	int		i;

	i = 0;
	if (ft_isalpha(var[i]) || var[i] == '_')
		i++;
	if (i == 0)
		return (put_errors(var));
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	if (var[i] != '\0' && var[i] != '=')
		return (put_errors(var));
	return (0);
}

char	**del_var(char **var, int bin)
{
	char	**new_var;
	int		i;
	int		iv;

	i = 0;
	iv = 0;
	new_var = malloc(sizeof(char *) * ft_strlen2d(var) - 1);
	if (!new_var)
		return (NULL);
	while (var[i])
	{
		if (i != bin)
		{
			new_var[iv++] = ft_strdup(var[i]);
			if (!*new_var)
			{
				ft_clear2d(new_var);
				return (NULL);
			}
		}
		i++;
	}
	new_var[iv] = NULL;
	ft_clear2d(var);
	return (new_var);
}
