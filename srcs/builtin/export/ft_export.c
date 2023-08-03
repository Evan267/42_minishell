/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <agallet@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:45:50 by agallet           #+#    #+#             */
/*   Updated: 2023/08/03 09:30:16 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_export(char *str)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (str[i] && str[i] != '=')
		printf("%c", str[i++]);
	if (str[i] != '=')
	{
		printf("\n");
		return ;
	}
	printf("%c\"", str[i++]);
	while (str[i])
		printf("%c", str[i++]);
	printf("\"\n");
}

int	ft_export(int argc, char **argv, char ***env)
{
	char	**var;
	char	**new_txt;
	int		i;
	int		ret;

	i = 0;
	if (argc == 1)
		return (call_export(*env));
	var = parse_var(argv);
	while (i < ft_strlen2d(var))
	{
		ret = laws_env(var[i]);
		if (ret == 1)
			var = del_var(var, i);
		i++;
	}
	var = same_var(var);
	new_txt = new_env(&var, *env);
	ft_clear2d(var);
	*env = new_txt;
	return (ret);
}
