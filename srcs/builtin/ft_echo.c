/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:04:29 by agallet           #+#    #+#             */
/*   Updated: 2023/06/20 12:31:36 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int argc, char **argv)
{
	int		i;
	int		start;

	start = 1;
	if (argc > 1 && argv[1] && !ft_strncmp(argv[1], "-n", ft_strlen("-n") + 1))
		start = 2;
	i = start;
	while (i < argc)
	{
		if (i == start)
			printf("%s", argv[i]);
		else
			printf(" %s", argv[i]);
		i++;
	}
	if ((argv[1] && ft_strncmp(argv[1], "-n", ft_strlen("-n") + 1))
		|| !argv[1])
		printf("\n");
	return (0);
}
