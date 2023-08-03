/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:43:47 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:18:12 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*define_path_history(char *history_path, char **env)
{
	char	*home;

	if (!history_path)
	{
		home = getvaluevar("HOME", env);
		if (!home)
			return (NULL);
		history_path = ft_strjoin(home, "/.minishell_history");
		free(home);
	}
	return (history_path);
}

int	open_history_file(int write_or_read, char **history_path, char **env)
{
	int			fd;

	*history_path = define_path_history(*history_path, env);
	if (!(*history_path))
		return (-1);
	if (write_or_read)
		fd = open(*history_path, O_RDONLY);
	else
		fd = open(*history_path, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		ft_putendl_fd("minishell: erreur d'ouverture de l'historique", 2);
		ft_putendl_fd("minishell va tenter de creer un fichier", 2);
	}
	return (fd);
}

void	reload_history(char	**history_path, char **env)
{
	int		fd;
	char	*line_file;

	line_file = NULL;
	fd = open_history_file(1, history_path, env);
	if (fd > 0)
		line_file = get_next_line(fd);
	while (line_file)
	{
		line_file[ft_strlen(line_file) - 1] = 0;
		add_history(line_file);
		free(line_file);
		line_file = NULL;
		line_file = get_next_line(fd);
	}
	if (fd != -1)
		close(fd);
}

void	save_history(char *line, char **history_path, char **env)
{
	int	fd;

	fd = open_history_file(0, history_path, env);
	if (fd > 0)
	{
		ft_putendl_fd(line, fd);
		close(fd);
	}
	add_history(line);
}
