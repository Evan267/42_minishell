/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:08:24 by agallet           #+#    #+#             */
/*   Updated: 2023/06/08 15:13:13 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


unsigned long long	ft_atoi_ulonglong(char *str)
{
	int		neg;
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
	int		neg;
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

int	error_exit(char *arg, char *msg, int ret)
{
	char	*error;
	char	*temp;

	temp = ft_strjoin("minishell: exit: ", arg);
	error = ft_strjoin(temp, msg);
	free(temp);
	ft_putendl_fd(error, 2);
	free(error);
	return (ret);
}

int	str_isNumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
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
	(void)argc;
	(void)argv;
	(void)env;
	
	code_exit = 0;
	if (argc > 2)
		code_exit = error_exit(argv[1], ": too many arguments", 1);
	else if (argc > 1)
	{
		code_exit = ft_atoi_uchar(argv[1]);
		if (ft_atoi_ulonglong(argv[1]) > 9223372036854775807
			|| str_isNumeric(argv[1]))
			code_exit = error_exit(argv[1],  ": numeric argument required", 255);
	}
	if (in_out)
		ft_putendl_fd("exit", in_out[3]);
	free(*env);
	exit(code_exit);
	return (0);
}
