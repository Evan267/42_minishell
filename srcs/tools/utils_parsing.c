/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:15:31 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:15:54 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_quote1(char **strchr, char *c, char *s, char **quote)
{
	strchr[0] = ft_strchr(s, c[0]);
	strchr[1] = ft_strchr(s, c[1]);
	if (strchr[0] && ft_strchr(strchr[0] + 1, c[0]))
	{
		quote[0] = ft_strchr(s, c[0]);
		quote[1] = ft_strchr(quote[0] + 1, c[0]);
	}
	else if (strchr[1] && ft_strchr(strchr[1] + 1, c[1]))
	{
		quote[0] = ft_strchr(s, c[1]);
		quote[1] = ft_strchr(quote[0], c[1]);
	}
	else
	{
		quote[0] = NULL;
		quote[1] = NULL;
	}
}

void	find_quote(char *s, char **quote)
{
	char	c[2];
	char	*strchr[2];
	int		i;

	i = 0;
	if ((ft_strchr(s, '\'') && quote[1] == ft_strchr(s, '\''))
		|| (ft_strchr(s, '\'') && quote[0] == ft_strchr(s, '\''))
		|| (ft_strchr(s, '\"') && quote[1] == ft_strchr(s, '\"'))
		|| (ft_strchr(s, '\"') && quote[0] == ft_strchr(s, '\"')))
		return ;
	if ((ft_strchr(s, '\'') && ft_strchr(s, '\'') < ft_strchr(s, '\"'))
		|| (ft_strchr(s, '\'') && !ft_strchr(s, '\"')))
	{
		c[0] = '\'';
		c[1] = '\"';
	}
	else
	{
		c[0] = '\"';
		c[1] = '\'';
	}
	find_quote1(strchr, c, s, quote);
}
