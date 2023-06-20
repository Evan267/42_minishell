#include "minishell.h"

void	infos_cmd(int **pipes, int *info_cmds, int *in_out, int *i)
{
 	if (info_cmds[0])
 	{
 		close_pipes(pipes, info_cmds[1]);
 		close_infile_outfile(in_out[0], in_out[1]);
 		exit(info_cmds[0]);
 	}
	after_fork(in_out, pipes, i);
	close_pipes(pipes, info_cmds[1]);
}

void	init_cmds(int *i, int *info_cmds, int **pid)
{
	i[0] = 0;
	i[1] = info_cmds[1];
	*pid = malloc(sizeof(pid_t) * i[1]);
}

void	check_fork(int *pid, int *i)
{
	if (pid[i[0]] == -1)
	{
		perror("fork");
		exit(127);
	}
}
