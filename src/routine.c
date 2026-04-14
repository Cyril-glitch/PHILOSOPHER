#include "../inc/philo.h"

static long	ft_timer(long start_time)
{
	return  (ft_gettime() - start_time);
}

static void	ft_meal(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->left_fork);
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time), MINT "has taken left fork" RESET);

	pthread_mutex_lock(cur_philo->right_fork);
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time), MINT "has taken right fork" RESET);

	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time), MINT "is " GOLD "eating" RESET);
    usleep(cur_philo->data->time_to_eat);
	cur_philo->last_meal = ft_gettime();

	
	pthread_mutex_unlock(cur_philo->left_fork);
	pthread_mutex_unlock(cur_philo->right_fork); 
}

static void	ft_sleep(t_philo *cur_philo)
{
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time), MINT "is "  L_BLUE "sleeping" RESET);
    usleep(cur_philo->data->time_to_sleep);
}

static void	ft_think(t_philo *cur_philo)
{
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time), MINT "is "  L_PURPLE "thinking" RESET);
}

void	*ft_routine(void *args)
{
	t_philo *cur_philo;

	cur_philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&cur_philo->data->stop_mutex);
		if (cur_philo->data->stop == 1)
			return (NULL);
		pthread_mutex_unlock(&cur_philo->data->stop_mutex);
        ft_meal(cur_philo);
		ft_sleep(cur_philo);	
		ft_think(cur_philo);
	}

	return (NULL);
}