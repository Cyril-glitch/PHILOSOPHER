/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:37:44 by cycolonn          #+#    #+#             */
/*   Updated: 2026/04/23 11:42:58 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_display_logs(t_philo *philo, long time, char *logs)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (ft_isfinish(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (0);
	}
	printf("%ld %d %s\n", time, philo->id, logs);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (1);
}

static void	ft_anti_queue(t_philo *cur_philo)
{
	if ((cur_philo->id & 1) && cur_philo->data->nb_philo > 1)
		ft_waiting(cur_philo->data->time_to_eat / 2, cur_philo);
}

int	ft_isfinish(t_philo *cur_philo)
{
	pthread_mutex_lock(&cur_philo->data->stop_mutex);
	if (cur_philo->data->stop == 1)
	{
		pthread_mutex_unlock(&cur_philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&cur_philo->data->stop_mutex);
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo	*cur_philo;

	cur_philo = (t_philo *)args;
	ft_start_line(cur_philo->data->start_time);
	ft_anti_queue(cur_philo);
	while (!ft_isfinish(cur_philo))
	{
		ft_meal(cur_philo);
		ft_sleep(cur_philo);
		ft_think(cur_philo);
	}
	return (NULL);
}

void	*ft_solo_routine(void *args)
{
	t_philo	*cur_philo;

	cur_philo = (t_philo *)args;
	ft_start_line(cur_philo->data->start_time);
	ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
		MINT "has taken right fork" RESET);
	while (!ft_isfinish(cur_philo))
		usleep(1000);
	return (NULL);
}
