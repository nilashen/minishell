#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	accumulator;

	sign = 1;
	while (*str == 32 || ((*str >= 9) && (*str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	accumulator = 0;
	while (*str >= 48 && *str <= 57)
	{
		accumulator = accumulator * 10 + (*str - 48);
		str++;
	}
	return (accumulator = sign * accumulator);
}
