/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:16:39 by eberger           #+#    #+#             */
/*   Updated: 2023/06/21 15:02:09 by eberger          ###   ########.fr       */
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

void	error_line(char *line, char *unexpected_token)
{
	char	*error;

	error = ft_strdup("minishell: syntax error near unexpected token `");
	error = join_3_str(error, unexpected_token, "\"");
	ft_putendl_fd(error, 2);
	add_history(line);
	free(line);
}

void	fork_test_line(char *line, int *pipes, int test)
{
	if (close(pipes[0]) == -1)
		perror("minishell");
	ft_putstr_fd(line, pipes[1]);
	free(line);
	while (test == 1 && !getstop())
	{
		line = readline("> ");
		if (!line)
			exit(258);
		test = test_lastchar(line);
		ft_putstr_fd(" ", pipes[1]);
		ft_putstr_fd(line, pipes[1]);
		free(line);
	}
	if (close(pipes[1]) == -1)
		perror("minishell");
	if (test)
		exit(test);
	exit(0);
}
