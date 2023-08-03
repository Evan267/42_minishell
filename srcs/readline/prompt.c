/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:27:45 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:18:46 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*user_place(char **env)
{
	char	*user;
	char	*tmp;
	char	*place;

	tmp = getvaluevar("USER", env);
	if (!tmp)
		return (NULL);
	user = ft_strjoin(tmp, "@");
	free(tmp);
	tmp = ft_strdup("MiNiShElL");
	place = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(user, place);
	free(user);
	free(place);
	return (tmp);
}

static char	*last_directory(char *cwd)
{
	char	*last;
	char	**directory;
	int		i;

	i = 0;
	last = NULL;
	directory = ft_split(cwd, '/');
	while (directory[i])
		i++;
	if (i)
		last = ft_strjoin(directory[i -1], " % ");
	i = 0;
	ft_clear2d(directory);
	return (last);
}

char	*add_second_part(char **env)
{
	char	*test;
	char	*cwd;
	char	*ret;

	cwd = NULL;
	test = getvaluevar("HOME", env);
	cwd = getcwd(cwd, 0);
	if (cwd && test && ft_strlen(cwd) == ft_strlen(test)
		&& ft_strncmp(cwd, test, ft_strlen(cwd)) == 0)
		ret = ft_strdup("~ % ");
	else
		ret = last_directory(cwd);
	if (!ret)
		ret = ft_strdup("% ");
	free(test);
	if (cwd)
		free(cwd);
	return (ret);
}

char	*readline_with_prompt(char **env)
{
	char	*second_part;
	char	*first_part;
	char	*str;
	char	*line;

	first_part = user_place(env);
	second_part = add_second_part(env);
	str = NULL;
	if (!first_part)
		str = ft_strdup("minishell$ ");
	if (!str && !second_part)
		str = ft_strdup("minishell$ ");
	else if (str && second_part)
		free(second_part);
	else
	{
		str = ft_strjoin(first_part, second_part);
		clear_prompt(second_part, first_part);
	}
	line = readline(str);
	if (!line)
		ctrl_d(str, env, 1);
	free(str);
	return (line);
}
