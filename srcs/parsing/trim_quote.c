/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:21:38 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 13:19:14 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	simple_or_double(char *str)
{
	char	*sple;
	char	*dble;

	sple = ft_strchr(str, '\'');
	dble = ft_strchr(str, '\"');
	if ((sple && !dble) || (sple && sple < dble))
		return ('\'');
	else
		return ('\"');
}

char	*delete_char(char *str, char *c)
{
	char	*ret;

	ret = ft_calloc(sizeof(char), ft_strlen(str));
	ft_strlcat(ret, str, c - str + 1);
	ft_strlcat(ret, c + 1, ft_strlen(str));
	free(str);
	return (ret);
}

char	*delete_quote(char *str)
{
	char	*first_quote;
	char	*second_quote;
	int		i;
	char	c;

	c = simple_or_double(str);
	i = 0;
	first_quote = ft_strchr(str, c);
	if (first_quote)
		second_quote = ft_strchr(first_quote + 1, c);
	while (first_quote && second_quote)
	{
		str = delete_char(str, first_quote);
		i = ft_strchr(str + i, c) - str;
		str = delete_char(str, str + i);
		c = simple_or_double(str + i);
		first_quote = ft_strchr(str + i, c);
		if (first_quote)
			second_quote = ft_strchr(first_quote + 1, c);
	}
	return (str);
}

char	**ft_trim_builtins(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		arg[i] = delete_quote(arg[i]);
		i++;
	}
	return (arg);
}
