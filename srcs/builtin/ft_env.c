/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:10 by agallet           #+#    #+#             */
/*   Updated: 2023/06/13 11:15:22 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int	argc, char **argv, char ***env)
{
	int i;
	int	j;
	(void)argv;

	i = 0;
	j = 0;
	if (argc != 1)
		return (1);
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '='))
			printf("%s\n", (*env)[i++]);
		else
			i++;
	}
	return (0);
}
