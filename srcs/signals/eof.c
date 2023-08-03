/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <eberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:34:37 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 09:16:18 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char *prompt, char **envp, int sw)
{
	if (sw)
	{
		tputs("\033[1A", 1, putchar);
		printf("%s exit\n", prompt);
		free(prompt);
		ft_clear2d(envp);
	}
	exit(0);
}
