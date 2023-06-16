/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*   Created: 2023/04/26 14:09:39 by eberger           #+#    #+#             */
/*   Updated: 2023/06/15 11:00:45 by eberger          ###   ########.fr       */
/*   Updated: 2023/06/16 14:17:12 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*multi_commands(int **pipes, char **cmds, char ***env, int *info_cmds)
{
	int		i[2];
	pid_t	*pid;
	int		in_out[2];

	i[0] = 0;
	i[1] = info_cmds[1];
	pid = malloc(sizeof(pid_t) * i[1]);
	while (i[0] < info_cmds[1])
	{
		info_cmds[0] = 0;
		cmds[i[0]] = infile_outfile(cmds[i[0]], in_out, info_cmds, env);
		pid[i[0]] = fork();
		if (pid[i[0]] == -1)
		{
			perror("fork");
			exit(127);
		}
		else if (pid[i[0]] == 0)
		{
			if (info_cmds[0])
			{
				close_pipes(pipes, info_cmds[1]);
				close_infile_outfile(in_out[0], in_out[1]);
				exit(info_cmds[0]);
			}
			after_fork(in_out, pipes, i);
			close_pipes(pipes, info_cmds[1]);
			if (!cmds[i[0]])
				exit(1);
			if (test_builtins(cmds[i[0]]))
				exec_builtins_fork(cmds[i[0]], env, test_builtins(cmds[i[0]]), NULL);
			else
				exec(cmds[i[0]], env);
		}
		i[0]++;
	}
	return (pid);
}

int	wait_all_forks(pid_t *pid, int len_cmds)
{
	int	i;
	int	status;

	i = 0;
	while (i < len_cmds)
	{
		pid[i] = waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	return (WEXITSTATUS(status));
}

int	one_builtin(char *cmd, char ***env, int status)
{
	int		i[2];
	int		in_out[4];
	char	*tmp;

	tmp = ft_strdup(cmd);
	i[0] = 0;
	i[1] = 1;
	saved_dup(in_out);
	tmp = infile_outfile(tmp, in_out, &status, env);
	if (!tmp)
		return (dup_in_out(in_out[2], in_out[3]), 1);
	after_fork(in_out, NULL, i);
	if (!status)
		status = exec_builtins(tmp, env, test_builtins(tmp), in_out);
	dup_in_out(in_out[2], in_out[3]);
	free(tmp);
	return (status);
}

int	execute_cmds(char *line, char ***env, int status)
{
	int		**pipes;
	char	**cmds;
	int		info_cmds[2];
	pid_t	*pid;
	
	line = replace_env_var(line, status, env);
	line = delete_pipe_outfile(line);
	cmds = ft_split_cmds(line, '|');
	info_cmds[0] = 0;
	info_cmds[1] = ft_strlen2d(cmds);
	if (info_cmds[1] == 1 && test_builtins(cmds[0]))
		info_cmds[0] = one_builtin(cmds[0], env, info_cmds[0]);
	else
	{
		pipes = create_pipes(info_cmds[1]);
		pid = multi_commands(pipes, cmds, env, info_cmds);
		stop_pipes(pipes, info_cmds[1]);
		info_cmds[0] = wait_all_forks(pid, info_cmds[1]);
	}
	free(line);
	ft_clear2d(cmds);
	return (info_cmds[0]);
}
