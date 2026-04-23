/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:37:51 by cycolonn          #+#    #+#             */
/*   Updated: 2026/04/23 11:43:49 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

long	ft_duration(long last_time)
{
	return (ft_gettime() - last_time);
}

void	ft_waiting(long pause, t_philo *cur_philo)
{
	long	start;

	start = ft_gettime();
	while (ft_duration(start) < (pause))
	{
		if (ft_isfinish(cur_philo))
			return ;
		usleep(500);
	}
}

void	ft_start_line(long start_time)
{
	while (ft_gettime() < start_time)
		usleep(500);
}
