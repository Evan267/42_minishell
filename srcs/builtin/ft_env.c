/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:10 by agallet           #+#    #+#             */
/*   Updated: 2023/08/07 12:20:19 by eberger          ###   ########.fr       */
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
