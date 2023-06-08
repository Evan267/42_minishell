/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:09:17 by eberger           #+#    #+#             */
/*   Updated: 2023/06/08 11:01:18 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_var(char *ret, int	*i, char *var)
{
	char	*new;
	int		len_var;

	len_var = ft_strlen(var);
	new = ft_calloc(sizeof(char), ft_strlen(ret) - i[1] + 1 + len_var);
	ft_strlcat(new, ret, i[0]);
	ft_strlcat(new, var, ft_strlen(new) + len_var + 1);
	ft_strlcat(new, ret + i[0] + i[1], ft_strlen(ret) - i[1] + 1 + len_var);
	free(ret);
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
	return (NULL);
}

char	*getvar(char *var_name, char **env, int status)
{
	if (*var_name == 0)
		return (NULL);
	else if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
		return (ft_itoa(status));
	else
		return (getvaluevar(var_name, env));
}

char	*replace_env_var(char *line, int status, char ***env)
{
	char	*ret;
	char	*var_info[2];
	int		i[2];
	int		quote;

	i[0] = 0;
	quote = 0;
	ret = ft_strdup(line);
	while (ret[i[0]])
	{
		i[1] = 0;
		if (ret[i[0]] == '\'')
			quote = !quote;
		else if (ret[i[0]] == '$' && !quote)
		{
			i[0]++;
			if (i[1] == 0 && ret[i[0] + i[1]] == '?')
				i[1]++;
			else
			{
				while (ft_isalpha(ret[i[0] + i[1]]))
					i[1]++;
			}
			if (i[1])
			{
				var_info[0] = ft_calloc(sizeof(char), i[1] + 1);
				ft_strlcpy(var_info[0], ret + i[0], i[1] + 1);
				var_info[1] = getvar(var_info[0], *env, status);
				ret = include_var(ret, i, var_info[1]);
			}
			i[0]--;
		}
		i[0]++;
	}
	free(line);
	return (ret);
}
