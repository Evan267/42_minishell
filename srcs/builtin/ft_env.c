/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:10 by agallet           #+#    #+#             */
/*   Updated: 2023/08/03 15:24:42 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, char ***env)
{
	int	i;

	i = 0;
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
