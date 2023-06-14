/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:10:05 by eberger           #+#    #+#             */
/*   Updated: 2023/06/14 15:14:30 by eberger          ###   ########.fr       */
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

char	test_consecutivepipe(char *line)
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

char	*test_line(char *line, int *save_status, char **history_path, char **envp)
{
	int	test;
	int	status;
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

	value_shlvl = 0;
	var = malloc(sizeof(char*) * 2);
	envp = ft_strdup2d(env);
	str_shlvl = getvaluevar("SHLVL", envp);
	if (str_shlvl)
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

void	unset_(char ***envp)
{
	char	**str;

	str = malloc(sizeof(char*) * 4);
	str[0] = ft_strdup("unset");
	str[1] = ft_strdup("_");
	str[2] = ft_strdup("OLDPWD");
	str[3] = NULL;
	ft_unset(3, str, envp);
	ft_clear2d(str);
}

void	setoldpwd(char ***envp)
{
	char	**str;

	str = malloc(sizeof(char*) * 3);
	str[0] = ft_strdup("export");
	str[1] = ft_strdup("OLDPWD");
	str[2] = NULL;
	ft_export(2, str, envp);
	ft_clear2d(str);
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
	char	*line;
	char	*history_path;
	int		status;
	char	**envp;
	(void)argv;

	if (argc > 1)
		return (ft_putendl_fd("Aucun argument necessaire", 2), 0);
	line = NULL;
	history_path = NULL;
	status = 0;
	envp = create_env(env);
	unset_(&envp);
	setoldpwd(&envp);
	reload_history(&history_path, envp);
	set_shell(1);
	while (1)
	{
		set_signals();
		setstop(0);
		line = readline_with_prompt(envp);
		if (line && ft_strlen(line) && str_isprint(line))
			line = test_line(line, &status, &history_path, envp);
		if (line && ft_strlen(line) && str_isprint(line))
		{
			exit_sig();
			save_history(line, &history_path, envp);
			status = execute_cmds(line, &envp, status);
			set_shell(0);
		}
	}
	return (1);
}
