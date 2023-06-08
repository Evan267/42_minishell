/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:10:05 by eberger           #+#    #+#             */
/*   Updated: 2023/06/08 14:04:46 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*add_readline(char *line)
{
	char	*read;

	read = readline("> ");
	if (!read)
		return (NULL);
	line = join_3_str(line, " ", read);
	return (line);
}

int	test_lastchar(char *line)
{
	int		i;
	char	last_char;

	i = 0;
	last_char = 0;
	while (line[i])
	{
		if (last_char == '|' && line[i] == last_char)
			return (3);
		if (line[i] > 32 && line[i] < 127)
			last_char = line[i];
		i++;
	}
	if (last_char == '|')
		return (1);
	if (last_char == '<' || last_char == '>')
		return (2);
	return (0);
}

char	*test_line(char *line, int *save_status, char *history_path, char **envp)
{
	int	test;
	int	status;

	test = test_lastchar(line);
	
	pipe_sigint();
	int	pid = fork();
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
	waitpid(pid, &status, 0);
	set_shell(0);
	if (WEXITSTATUS(status))
	{
		save_history(line, history_path, envp);
		*save_status = 258;
		if (WEXITSTATUS(status) == 1)
			*save_status = 1;
		return (NULL);
	}
	else
		return (line);
}

char	**create_env(char **env)
{
	char	**envp;
	char	**var;
	char	*str_shlvl;
	int		value_shlvl;

	var = malloc(sizeof(char*) * 2);
	envp = ft_strdup2d(env);
	str_shlvl = getvaluevar("SHLVL", envp);
	value_shlvl = ft_atoi(str_shlvl);
	value_shlvl++;
	free(str_shlvl);
	str_shlvl = ft_itoa(value_shlvl);
	var[0] = ft_strjoin("SHLVL=", str_shlvl);
	var[1] = NULL;
	free(str_shlvl);
	envp = new_env(&var, envp);
	ft_clear2d(var);
	return (envp);
}

void	set_shell(int sw)
{
	static	struct	termios	term;

	if (sw)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	static char	*history_path;
	int			status;
	char		**envp;
	(void)argv;

	if (argc > 1)
		return (ft_putendl_fd("Aucun argument necessaire", 2), 0);
	line = NULL;
	status = 0;
	envp = create_env(env);
	reload_history(history_path, envp);
	set_shell(1);
	while (1)
	{
		set_signals();
		setstop(0);
		line = readline_with_prompt(envp);
		line = test_line(line, &status, history_path, envp);
		if (line && ft_strlen(line))
		{
			exit_sig();
			save_history(line, history_path, envp);
			status = execute_cmds(line, &envp, status);
			set_shell(0);
		}
	}
	return (1);
}
