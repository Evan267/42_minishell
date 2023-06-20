/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:05 by eberger           #+#    #+#             */
/*   Updated: 2023/06/19 13:41:54 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	permission_denied(char *command)
{
	char	*error[2];

	error[0] = ft_strjoin("minishell: ", command);
	error[1] = ft_strjoin(error[0], ": Permission denied");
	ft_putendl_fd(error[1], 2);
	free(error[0]);
	free(error[1]);
	exit(126);
}

int	command_not_found(char *command)
{
	char	*error[2];

	error[0] = ft_strjoin("minishell: ", command);
	error[1] = ft_strjoin(error[0], ": command not found");
	ft_putendl_fd(error[1], 2);
	free(error[0]);
	free(error[1]);
	exit(127);
}

int	no_file_directory(char *command)
{
	char	*error[2];

	error[0] = ft_strjoin("minishell: ", command);
	error[1] = ft_strjoin(error[0], ": No such file or directory");
	ft_putendl_fd(error[1], 2);
	free(error[0]);
	free(error[1]);
	exit(127);
}
