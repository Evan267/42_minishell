/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:19:00 by eberger           #+#    #+#             */
/*   Updated: 2023/08/14 12:33:49 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *command, char *envp_path)
{
	char	**paths;
	char	*cmd_path;
	char	*cmd;
	int		i;

	if (ft_strlen(command) == 0)
		return (NULL);
	if (!envp_path)
		return (command_not_found(command), command);
	paths = ft_split(envp_path, ':');
	cmd = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
			return (free(cmd), ft_clear2d(paths), cmd_path);
		i++;
		free(cmd_path);
	}
	free(cmd);
	ft_clear2d(paths);
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
			command_not_found(args[0]);
		permission_denied(args[0]);
	}
	else if (access(path, X_OK))
	{
		if (args[0][0] == '.' || args[0][0] == '/')
			no_file_directory(args[0]);
		command_not_found(args[0]);
	}
	if (!access(args[0], X_OK)
		&& path[0] == '.' && path[1] == '/' && !S_ISDIR(info.st_mode))
		command_not_found(args[0]);
	return (path);
}
