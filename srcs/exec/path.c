/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:19:00 by eberger           #+#    #+#             */
/*   Updated: 2023/06/19 10:14:53 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *command, char *envp_path)
{
	char	**paths;
	char	*cmd_path;
	char	*cmd;
	int		i;

	if (ft_strlen(command) == 0)
		return (NULL);
	paths = ft_split(envp_path, ':');
	cmd = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
			return (free(cmd), cmd_path);
		i++;
		free(cmd_path);
	}
	free(cmd);
	if (!access(command, F_OK))
		return (command);
	return (NULL);
}

char	*ft_path(char **args, char *envpath)
{
	char		*path;
	struct stat	info;
	
	path = find_path(args[0], envpath);
	stat(path, &info);
	if (!access(path, F_OK) && access(path, X_OK) && !S_ISDIR(info.st_mode))
	{
		if (args[0][0] != '.' && args[0][0] != '/')
		{
			ft_putendl_fd("minishell: command not found", 2);
			exit(127);
		}
		permission_denied(args[0]);
	}
	else if (access(path, X_OK))
	{
		if (args[0][0] == '.' || args[0][0] == '/')
		{
			ft_putendl_fd("minishell: No such file or directory", 2);
			exit(127);
		}
		command_not_found(args[0]);
	}
	return (path);
}
