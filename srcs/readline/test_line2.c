/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:16:39 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 16:17:59 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_isprint(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	error_line(char *line, char *unexpected_token)
{
	char	*error;

	error = ft_strdup("minishell: syntax error near unexpected token `");
	error = join_3_str(error, unexpected_token, "\"");
	ft_putendl_fd(error, 2);
	add_history(line);
	free(line);
	return (258);
}
