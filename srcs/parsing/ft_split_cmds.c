/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:52:59 by eberger           #+#    #+#             */
/*   Updated: 2023/04/26 14:10:27 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_clear(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (0);
}

static void	find_quote(char *s, char **quote)
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

static unsigned int	ft_count_string(char *str, char c)
{
	int		count;
	char	*strchr;
	char	*quote_p[2];

	count = 0;
	while (*str)
	{
		strchr = ft_strchr(str, c);
		find_quote(str, quote_p);
		if ((strchr > str && strchr < quote_p[0]) || strchr > quote_p[1])
			count++;
		if (strchr != 0)
			str = ft_strchr(str, c) + 1;
		else
		{
			count++;
			break ;
		}
	}
	return (count);
}

static char	**ft_part(char **ret, unsigned int *k, const char *s, char c)
{
	char	*strchr;

	strchr = ft_strchr(s + k[1], c);
	if (strchr)
	{
		if (strchr - s > k[1])
		{
			ret[k[0]] = malloc(strchr - s - k[1] + 1);
			if (!ret[k[0]])
				return (ft_clear(ret));
			ft_strlcpy(ret[k[0]], (char *)(s + k[1]), strchr - s - k[1] + 1);
			(k[0])++;
		}
		k[1] = strchr - s + 1;
	}
	else if (k[2])
	{
		ret[k[0]] = malloc(k[2] + 1);
		if (!ret[k[0]])
			return (ft_clear(ret));
		ft_strlcpy(ret[k[0]], (char *)(s + k[1]), k[2] + 1);
		(k[0])++;
		k[1] = k[1] + k[2];
	}
	return (ret);
}

static char	**ft_add_part(const char *s, char c, char **ret)
{
	unsigned int	k[3];
	char	*quote[2];

	k[0] = 0;
	k[1] = 0;
	while ((ft_strchr(s + k[1], c) != 0 || ft_strlen(s + k[1])) && *s)
	{
		k[2] = (unsigned int)ft_strlen(s + k[1]);
		find_quote((char *)(s + k[1]), quote);
		if (ft_strchr(s + k[1], c) > quote[0] && ft_strchr(s + k[1], c) < quote[1])
		{
			ret[k[0]] = ft_calloc(sizeof(char), quote[1] - quote[0] + 1);
			if (!ret[k[0]])
				return (ft_clear(ret));
			ft_strlcpy(ret[k[0]], quote[0], quote[0] - quote[1] + 1);
			(k[0])++;
			k[1] = quote[1] - s + 1;
		}
		else if (!ft_part(ret, k, s, c))
			return (0);
	}
	ret[k[0]] = 0;
	return (ret);
}

char	**ft_split_cmds(char const *s, char c)
{
	unsigned int	len_ptr;
	char			**ret;

	if (!s)
		return (0);
	if (!c && *s)
	{
		ret = malloc (sizeof(char *) * 2);
		if (!ret)
			return (0);
		ret[0] = malloc (sizeof(char) * (ft_strlen(s) + 1));
		if (!ret[0])
			return (ft_clear(ret));
		ft_strlcpy(ret[0], s, ft_strlen(s) + 1);
		ret[1] = 0;
		return (ret);
	}
	len_ptr = ft_count_string((char *)s, c);
	ret = malloc (sizeof(char *) * (len_ptr + 1));
	if (!ret)
		return (0);
	return (ft_add_part(s, c, ret));
}
