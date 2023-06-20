/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:59:35 by agallet           #+#    #+#             */
/*   Updated: 2023/06/20 13:13:06 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Affichage */
static int	verif_tab(int *tab, int index, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (tab[i] == index)
			return (1);
		i++;
	}
	return (0);
}

static int	longest_str(char *str1, char *str2)
{
	int	length1;
	int	length2;

	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	if (length1 > length2)
		return (length1);
	else
		return (length2);
}

static	int	not_in_tab(int *tab, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (!verif_tab(tab, i, length))
			return (i);
		i++;
	}
	return (0);
}

static	int	*set_tab(int *length, char **env)
{
	int	i;
	int	*tab;

	*length = ft_strlen2d(env);
	i = 0;
	tab = malloc(sizeof(int) * (*length));
	while (i < *length)
		tab[i++] = -1;
	return (tab);
}

int	call_export(char **env)
{
	char	*temp;
	int		*tab;
	int		nb[4];

	ft_bzero(nb, 4 * sizeof(int));
	tab = set_tab(nb + 3, env);
	while (nb[0] < nb[3])
	{
		nb[1] = 0;
		temp = env[not_in_tab(tab, nb[3])];
		tab[nb[0]] = not_in_tab(tab, nb[3]);
		while (env[nb[1]])
		{
			nb[2] = ft_strncmp(env[nb[1]], temp, longest_str(env[nb[1]], temp));
			if (nb[2] < 0 && !verif_tab(tab, nb[1], nb[3]))
			{
				temp = env[nb[1]];
				tab[nb[0]] = nb[1];
			}
			nb[1] = nb[1] + 1;
		}
		put_export(temp);
		nb[0] = nb[0] + 1;
	}
	return (free(tab), 0);
}
