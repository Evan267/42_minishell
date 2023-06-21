/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:01:14 by eberger           #+#    #+#             */
/*   Updated: 2023/06/21 15:03:13 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	test_lastchar(char *line)
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

static int	wait_line(pid_t pid, int *status, char *line)
{
	int	status_pid;

	waitpid(pid, &status_pid, 0);
	set_shell(0);
	if (WEXITSTATUS(status_pid))
	{
		if (WEXITSTATUS(status) == 3)
			error_line(line, "|");
		else if (WEXITSTATUS(status) == 2)
			error_line(line, "newline");
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
	int		pipes[2];

	test = test_lastchar(line);
	pipe_sigint();
	if (pipe(pipes) == -1)
	{
		perror("minishell");
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
		fork_test_line(line, pipes, test);
	if (close(pipes[1]) == -1)
		perror("minishell");
	free(line);
	line = get_next_line(pipes[0]);
	if (close(pipes[0]) == -1)
		perror("minishell");
	if (wait_line(pid, status, line))
		return (save_history(line, hstry_path, envp), NULL);
	else
		return (line);
}
