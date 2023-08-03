/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:42:18 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:15:36 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_3_str(char *str1, char *str2, char *str3)
{
	char	*c;

	c = str1;
	str1 = ft_strjoin(str1, str2);
	free(c);
	c = str1;
	str1 = ft_strjoin(str1, str3);
	free(c);
	return (str1);
}

char	*ft_joinsplit(char **split)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (split[i])
	{
		if (len && ft_strlen(split[i]))
			len++;
		len += ft_strlen(split[i]);
		i++;
	}
	ret = ft_calloc(sizeof(char), len + 1);
	i = 0;
	while (split[i])
	{
		if (ft_strlen(ret) && ft_strlen(split[i]))
			ft_strlcat(ret, " ", len + 1);
		ft_strlcat(ret, split[i], len + 1);
		i++;
	}
	return (ret);
}

void	trim_by_char(char **ret, char c)
{
	char	*tmp;
	char	trim[2];

	trim[0] = c;
	trim[1] = 0;
	tmp = *ret;
	*ret = ft_strtrim(*ret, trim);
	free(tmp);
}

char	*delete_pipe_outfile(char *line)
{
	char	*test;

	test = ft_strnstr(line, ">|", ft_strlen(line));
	if (test)
		line = delete_char(line, test + 1);
	return (line);
}

char	*empty_str(char *str)
{
	free(str);
	return (ft_calloc(sizeof(char), 1));
}
