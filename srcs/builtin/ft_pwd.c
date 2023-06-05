/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:00:20 by agallet           #+#    #+#             */
/*   Updated: 2023/05/29 12:09:05 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*a modifier en utilisant getcwd a la place de getenv*/
int	ft_pwd(int argc, char **argv)
{
	char *str;

	if (argc < 1)
		return (1);
	if (!ft_strnstr(argv[0], "pwd", 3))
		return (1);
	str = getenv("PWD");
	if (!str)
	{
		perror("");
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}

