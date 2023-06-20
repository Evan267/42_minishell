/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:52:59 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 15:20:11 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_words(const char *str, char c)
{
	int		count;
	char	*strchr;
	char	*quote_p[2];

	count = 0;
	quote_p[0] = NULL;
	quote_p[1] = NULL;
	while (*str)
	{
		strchr = ft_strchr(str, c);
		find_quote((char *)str, quote_p);
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

static char	*word_dup(const char *str, int *start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - *start + 1) * sizeof(char));
	while (*start < finish)
		word[i++] = str[(*start)++];
	word[i] = '\0';
	*start = -1;
	return (word);
}

static char	**init_split(char const *s, char c, size_t *i, char **quote)
{
	char	**split;

	quote[0] = NULL;
	quote[1] = NULL;
	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	return (split);
}

char	**ft_split_cmds(char const *s, char c)
{
	size_t	i[2];
	int		index;
	char	**split;
	char	*quote_p[2];

	split = init_split(s, c, (size_t *)i, (char **)quote_p);
	if (!split)
		return (NULL);
	index = -1;
	while (i[0] <= ft_strlen(s))
	{
		find_quote((char *)s + i[0], quote_p);
		if (s + i[0] == quote_p[0])
		{
			if (s[i[0]] != c && index < 0)
				index = i[0];
			i[0] = quote_p[1] - s + 1;
		}
		if (s[i[0]] != c && index < 0)
			index = i[0];
		else if ((s[i[0]] == c || i[0] == ft_strlen(s)) && index >= 0)
			split[(i[1])++] = word_dup(s, &index, i[0]);
		(i[0])++;
	}
	return (split[i[1]] = 0, split);
}
