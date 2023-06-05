#include "libft.h"
#include <stdio.h>
int	ft_strlen2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
