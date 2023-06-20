/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:01:14 by eberger           #+#    #+#             */
/*   Updated: 2023/06/20 16:18:05 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_readline(char *line)
{
	char	*read;

	read = readline("> ");
	if (!read)
		return (NULL);
	line = join_3_str(line, " ", read);
	return (line);
}

static char	test_consecutivepipe(char *line)
{
	int		i;
	char	*quote_p[2];
	char	last_char;

	quote_p[0] = NULL;
	quote_p[1] = NULL;
	last_char = 0;
	i = 0;
	while (line[i])
	{
		if (line + i > quote_p[1])
			find_quote(line + i, quote_p);
		if (last_char == '|' && line[i] == last_char
			&& line + i < quote_p[0] && line + i > quote_p[1])
			return (0);
		if (line[i] > 32 && line[i] < 127)
			last_char = line[i];
		i++;
	}
	return (last_char);
}

static int	test_lastchar(char *line)
{
	int		i;
	char	last_char;

	i = 0;
	last_char = test_consecutivepipe(line);
	if (!last_char)
		return (3);
	if (last_char == '|')
		return (1);
	if (last_char == '<' || last_char == '>')
		return (2);
	return (0);
}

static int	wait_line(pid_t pid, int *status)
{
	int	status_pid;

	waitpid(pid, &status_pid, 0);
	set_shell(0);
	if (WEXITSTATUS(status_pid))
	{
		*status = 258;
		if (WEXITSTATUS(status) == 1)
			*status = 1;
		return (1);
	}
	else
		return (0);
}

char	*test_line(char *line, int *status, char **hstry_path, char **envp)
{
	int		test;
	pid_t	pid;

	test = test_lastchar(line);
	pipe_sigint();
	pid = fork();
	if (pid == 0)
	{
		while (test == 1 && !getstop())
		{
			line = add_readline(line);
			if (!line)
				exit(258);
			test = test_lastchar(line);
		}
		if (test == 3)
			exit(error_line(line, "|"));
		else if (test == 2)
			exit(error_line(line, "newline"));
		exit(0);
	}
	if (wait_line(pid, status))
		return (save_history(line, hstry_path, envp), NULL);
	else
		return (line);
}
