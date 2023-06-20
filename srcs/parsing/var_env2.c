/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:25:21 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 15:48:20 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvaluevar(char *var_name, char **env)
{
	int		i;
	char	*test;
	int		len;

	i = 0;
	test = ft_strjoin(var_name, "=");
	len = ft_strlen(test);
	while (env[i])
	{
		if (ft_strnstr(env[i], test, len))
		{
			free(test);
			return (ft_substr(env[i], len, ft_strlen(env[i]) - len));
		}
		i++;
	}
	if (test)
		free(test);
	return (NULL);
}

char	*change_var(char *ret, int	*i, char *var)
{
	char	*new;
	int		len_var;

	len_var = ft_strlen(var);
	new = ft_calloc(sizeof(char), ft_strlen(ret) - i[1] + 1 + len_var);
	if (!new)
		return (NULL);
	ft_strlcat(new, ret, i[0]);
	ft_strlcat(new, var, ft_strlen(new) + len_var + 1);
	ft_strlcat(new, ret + i[0] + i[1], ft_strlen(ret) - i[1] + 1 + len_var);
	return (new);
}

char	*include_var(char *ret, int *i, char *var)
{
	char	var_null[1];

	if (!var)
	{
		var_null[0] = 0;
		var = var_null;
	}
	return (change_var(ret, i, var));
}
