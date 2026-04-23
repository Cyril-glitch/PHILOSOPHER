/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:37:18 by cycolonn          #+#    #+#             */
/*   Updated: 2026/04/23 11:37:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_isfull_dig(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*(s++)))
			return (0);
	}
	return (1);
}

int	ft_overflow(t_data *data)
{
	if (data->nb_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->must_eat < 0)
	{
		free(data);
		return (ft_putstr_fd(BL_RED "WRONG ARGUMENT\n" RESET, 2), 1);
	}
	return (0);
}
