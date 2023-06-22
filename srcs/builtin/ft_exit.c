/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:08:24 by agallet           #+#    #+#             */
/*   Updated: 2023/06/22 10:32:41 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	ft_atoi_ulonglong(char *str)
{
	int					neg;
	unsigned long long	value;

	neg = 0;
	value = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (neg)
		value = 9223372036854775807 - value + 1;
	return (value);
}

char	ft_atoi_uchar(char *str)
{
	int				neg;
	unsigned char	value;

	neg = 0;
	value = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (neg)
		value = 256 - value;
	return (value);
}

int	err_ex(char *arg, char *msg, int ret)
{
	char	*error;
	char	*temp;

	if (arg)
		temp = ft_strjoin("minishell: exit: ", arg);
	else
		temp = ft_strdup("minishell: exit");
	error = ft_strjoin(temp, msg);
	free(temp);
	ft_putendl_fd(error, 2);
	free(error);
	return (ret);
}

int	str_islonglong(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 19)
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(int argc, char **argv, char ***env, int *in_out)
{
	unsigned char	code_exit;

	code_exit = 0;
	if (in_out)
		ft_putendl_fd("exit", in_out[3]);
	if (argc > 2 && !str_islonglong(argv[1])
		&& ft_atoi_ulonglong(argv[1]) <= 9223372036854775807)
		return (err_ex(NULL, ": too many arguments", 1));
	if (argc > 1)
	{
		if (str_islonglong(argv[1])
			|| ft_atoi_ulonglong(argv[1]) > 9223372036854775807)
			code_exit = err_ex(argv[1], ": numeric argument required", 255);
		else
			code_exit = ft_atoi_uchar(argv[1]);
	}
	ft_clear2d(*env);
	exit(code_exit);
	return (0);
}
