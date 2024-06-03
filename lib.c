#include "philo.h"

int	ft_atoi(char *str)
{
	int	x;
	int	re;
	int	sin;

	x = 0;
	re = 0;
	sin = 1;
	while ((str[x] >= 9 && str[x] <= 13) || str[x] == 32)
		x++;
	if (str[x] == '-')
	{
		sin *= -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] >= 48 && str[x] <= 57)
	{
		re *= 10;
		re += str[x] - 48;
		x++;
	}
	return (re * sin);
}