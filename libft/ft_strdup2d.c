/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:05:40 by eberger           #+#    #+#             */
/*   Updated: 2023/04/27 12:13:55 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup2d(char **str)
{
	char	**ret;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen2d(str);
	ret = malloc(sizeof(*str) * (len + 1));
	while (i < len)
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
