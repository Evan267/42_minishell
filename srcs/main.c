/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:10:05 by eberger           #+#    #+#             */
/*   Updated: 2023/06/05 11:04:15 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_line(char *line, char *unexpected_token)
{
	char	*error;

	error = ft_strdup("minishell: syntax error near unexpected token `");
	error = join_3_str(error, unexpected_token, "\"");
	ft_putendl_fd(error, 2);
	add_history(line);
	free(line);
	return (NULL);
}

char	*add_readline(char *line)
{
	char	*read;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	else if (pid == 0)
	{
		read = readline("> ");
		line = join_3_str(line, " ", read);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (line);
}

char	*test_line(char *line)
{
	int		i;
	char	last_char;

	i = 0;
	last_char = 0;
	while (line[i])
	{
		if (last_char == '|' && line[i] == last_char)
			return (error_line(line, "|"));
		if (line[i] > 32 && line[i] < 127)
			last_char = line[i];
		i++;
	}
	if (last_char == '|')
	{
		line = add_readline(line);
		line = test_line(line);
	}
	if (last_char == '<' || last_char == '>')
		return (error_line(line, "newline"));
	return (line);
}

char	**create_env(char **env)
{
	char	**envp;
	char	*var[2];
	char	*str_shlvl;
	int		value_shlvl;

	envp = ft_strdup2d(env);
	str_shlvl = getvaluevar("SHLVL", envp);
	value_shlvl = ft_atoi(str_shlvl);
	value_shlvl++;
	free(str_shlvl);
	str_shlvl = ft_itoa(value_shlvl);
	var[0] = ft_strjoin("SHLVL=", str_shlvl);
	var[1] = NULL;
	free(str_shlvl);
	envp = new_env(var, envp);
	free(var[0]);
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
	envp = create_env(env);
	reload_history(history_path, envp);
	set_shell(1);
	while (1)
	{
		set_signals();
		line = readline_with_prompt(envp);
		line = test_line(line);
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
