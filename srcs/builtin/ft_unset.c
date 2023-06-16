/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:52 by agallet           #+#    #+#             */
/*   Updated: 2023/06/16 14:33:35 by eberger          ###   ########.fr       */
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
	if (env[i])
		return (i);
	return (-1);
}

int	ft_unset(int argc, char **argv, char ***env)
{
	int	i;
	int	nb;

	i = 1;
	if (argc == 1)
		return (0);
	while (argv[i])
	{
		nb = search_var(argv[i], *env);
		if (nb != -1)
			*env = del_var(*env, nb);
		i++;
	}
	return (0);
}
