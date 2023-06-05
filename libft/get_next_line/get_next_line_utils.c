/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:52:19 by eberger           #+#    #+#             */
/*   Updated: 2023/06/02 14:31:04 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear_gnl(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

int	ft_linelen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == 0)
		return (-1);
	i++;
	return (i);
}

void	*ft_realloc(void *ptr, size_t size, size_t msize)
{
	void	*new;
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	if (size <= msize)
		return (ptr);
	new = ft_calloc(1, size);
	if (!new)
		return (ft_clear_gnl(&str));
	if (str)
	{
		while (str[i])
			i++;
		ft_strlcat(new, str, i + 1);
		free(str);
	}
	return (new);
}
