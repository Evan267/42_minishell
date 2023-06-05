/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:52 by agallet           #+#    #+#             */
/*   Updated: 2023/05/29 13:46:23 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	search_var(char *str, char **env)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(str);
	while (env[i] && ft_strncmp(env[i], str, length))
		i++;
	return (i);
}

int	ft_unset(int argc, char **argv, char ***env)
{
	int		i;
	char	*str;

	i = 1;
	if (argc == 1)
		return (1);
	while (argv[i])
	{
		str = getenv(argv[i]);
		if (str)
			del_var(&str, search_var(str, *env));
		i++;
	}
	return (0);
}
