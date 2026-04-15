#include "../inc/philo.h"

static void	ft_meal(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->right_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "has taken right fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->right_fork);
		return ;
	}
	pthread_mutex_lock(cur_philo->left_fork);
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "has taken left fork" RESET))
	{
		pthread_mutex_unlock(cur_philo->left_fork);
		pthread_mutex_unlock(cur_philo->right_fork);
		return ;
	}
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " GOLD "eating" RESET))
	{
		pthread_mutex_unlock(cur_philo->left_fork);
		pthread_mutex_unlock(cur_philo->right_fork);
		return ;
	}
	ft_waiting(cur_philo->data->time_to_eat, cur_philo);
	cur_philo->last_meal = ft_gettime();
	cur_philo->meals_eaten++;
	pthread_mutex_unlock(cur_philo->right_fork);
	pthread_mutex_unlock(cur_philo->left_fork);
}

static void	ft_sleep(t_philo *cur_philo)
{
	if (!ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " L_BLUE "sleeping" RESET))
		return ;
	ft_waiting(cur_philo->data->time_to_sleep, cur_philo);
}

static void	ft_think(t_philo *cur_philo)
{
	ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "is " L_PURPLE "thinking" RESET);
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
	t_philo *cur_philo;

	cur_philo = (t_philo *)args;
	if (cur_philo->id & 1)
		ft_waiting(cur_philo->data->time_to_eat + 100, cur_philo);
	while (1)
	{
		if (ft_isfinish(cur_philo))
			return (NULL);
		ft_meal(cur_philo);
		ft_sleep(cur_philo);
		ft_think(cur_philo);
	}
	return (NULL);
}