/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:23:56 by eberger           #+#    #+#             */
/*   Updated: 2023/06/12 13:03:26 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t type)
{
	void	*new;
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	new = ft_calloc(type, size);
	if (!new)
		return (ft_clear2d(&str));
	if (str)
	{
		while (str[i])
			i++;
		ft_strlcat(new, str, i + 1);
		ft_bzero(ptr, ft_strlen(str));
		free(str);
	}
	return (new);
}
