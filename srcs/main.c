/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:10:05 by eberger           #+#    #+#             */
/*   Updated: 2023/06/22 10:15:54 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*history_path;
	int		status;
	char	**envp;

	(void)argv;
	if (argc > 1)
		return (ft_putendl_fd("Aucun argument necessaire", 2), 0);
	envp = init(&line, env, &history_path, &status);
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
