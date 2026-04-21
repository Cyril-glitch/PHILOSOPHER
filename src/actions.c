#include "../inc/philo.h"

int	ft_right_fork(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->right_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "has taken right fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->right_fork);
		if (cur_philo->left_fork < cur_philo->right_fork)
			pthread_mutex_unlock(cur_philo->left_fork);
		return 0;
	}
	return 1;
}

int	ft_left_fork(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->left_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "has taken left fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->left_fork);
		if (cur_philo->left_fork > cur_philo->right_fork)
			pthread_mutex_unlock(cur_philo->right_fork);
		return 0;
	}
	return 1;
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
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " GOLD "eating" RESET))
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
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " L_BLUE "sleeping" RESET))
		return ;
	ft_waiting(cur_philo->data->time_to_sleep, cur_philo);
}

void	ft_think(t_philo *cur_philo)
{
	long	time_to_think;

	time_to_think = 0;
	ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " L_PURPLE "thinking" RESET);
	if (cur_philo->data->out_of_play)
	{
		time_to_think = cur_philo->data->out_of_play - (cur_philo->data->time_to_eat + cur_philo->data->time_to_sleep);
		ft_waiting(time_to_think, cur_philo);	
		usleep(500);
	}	
}


