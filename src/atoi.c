#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi(const char *nptr)
{
	int	signe;
	int	res;
	int	i;

	i = 0;
	res = 0;
	signe = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res *= 10 ;
		res += nptr[i] - '0';
		i++;
	}
	return (res * signe);
}