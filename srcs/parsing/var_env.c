/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:09:17 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 15:49:42 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvar(char *var_name, char **env, int status)
{
	if (*var_name == 0)
		return (NULL);
	else if (!ft_strncmp(var_name, "?", ft_strlen(var_name)))
		return (ft_itoa(status));
	else
		return (getvaluevar(var_name, env));
}

static void	new_line_var(char **line, char **new, char **var_info)
{
	free(*line);
	*line = ft_strdup(*new);
	free(*new);
	free(var_info[0]);
	free(var_info[1]);
}

char	*add_var(char *line, int status, char ***env, int *j)
{
	char	*var_info[2];
	char	*new;

	var_info[0] = NULL;
	var_info[1] = NULL;
	j[0]++;
	if (j[1] == 0 && line[j[0] + j[1]] == '?')
		j[1]++;
	else
	{
		while (ft_isalpha(line[j[0] + j[1]]))
			j[1]++;
	}
	if (j[1])
	{
		var_info[0] = ft_calloc(sizeof(char), j[1] + 1);
		if (!var_info[0])
			return (line);
		ft_strlcpy(var_info[0], line + j[0], j[1] + 1);
		var_info[1] = getvar(var_info[0], *env, status);
		new = include_var(line, j, var_info[1]);
		new_line_var(&line, &new, var_info);
	}
	return (line);
}

char	*replace_env_var(char *line, int status, char ***env)
{
	int		i[2];
	int		quote;

	i[0] = 0;
	quote = 0;
	while (line[i[0]])
	{
		i[1] = 0;
		if (line[i[0]] == '\'')
			quote = !quote;
		else if (line[i[0]] == '$' && !quote)
			line = add_var(line, status, env, i);
		i[0]++;
	}
	return (line);
}
