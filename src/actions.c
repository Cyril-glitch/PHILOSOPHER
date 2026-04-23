/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:36:39 by cycolonn          #+#    #+#             */
/*   Updated: 2026/04/23 11:42:00 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_right_fork(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->right_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
			MINT "has taken a fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->right_fork);
		if (cur_philo->left_fork < cur_philo->right_fork)
			pthread_mutex_unlock(cur_philo->left_fork);
		return (0);
	}
	return (1);
}

int	ft_left_fork(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->left_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
			MINT "has taken a fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->left_fork);
		if (cur_philo->left_fork > cur_philo->right_fork)
			pthread_mutex_unlock(cur_philo->right_fork);
		return (0);
	}
	return (1);
}

void	ft_meal(t_philo *cur_philo)
{
	if (cur_philo->left_fork < cur_philo->right_fork)
	{
		if (!ft_left_fork(cur_philo) || !ft_right_fork(cur_philo))
			return ;
	}
	else
	{
		if (!ft_right_fork(cur_philo) || !ft_left_fork(cur_philo))
			return ;
	}
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
			MINT "is " GOLD "eating" RESET))
	{
		pthread_mutex_unlock(cur_philo->left_fork);
		pthread_mutex_unlock(cur_philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&cur_philo->data->meal_mutex);
	cur_philo->last_meal = ft_gettime();
	cur_philo->meals_eaten++;
	pthread_mutex_unlock(&cur_philo->data->meal_mutex);
	ft_waiting(cur_philo->data->time_to_eat, cur_philo);
	pthread_mutex_unlock(cur_philo->left_fork);
	pthread_mutex_unlock(cur_philo->right_fork);
}

void	ft_sleep(t_philo *cur_philo)
{
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
			MINT "is " L_BLUE "sleeping" RESET))
		return ;
	ft_waiting(cur_philo->data->time_to_sleep, cur_philo);
}

void	ft_think(t_philo *cur_philo)
{
	long	time_to_think;

	time_to_think = 0;
	ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),
		MINT "is " L_PURPLE "thinking" RESET);
	if (cur_philo->data->nb_philo & 1)
	{
		time_to_think = (cur_philo->data->time_to_eat * 2)
			- cur_philo->data->time_to_sleep;
		if (time_to_think)
			ft_waiting(time_to_think, cur_philo);
	}
}
