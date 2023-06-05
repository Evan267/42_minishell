/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:19:00 by eberger           #+#    #+#             */
/*   Updated: 2023/04/26 14:10:27 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *command, char *envp_path)
{
	char	**paths;
	char	*cmd_path;
	char	*cmd;
	int		i;

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
	char	*path;

	path = find_path(args[0], envpath);
	if (!access(path, F_OK) && access(path, X_OK))
		permission_denied(args[0]);
	else if (access(path, X_OK))
		command_not_found(args[0]);
	return (path);
}
