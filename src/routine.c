#include "../inc/philo.h"

static void	ft_meal(t_philo *cur_philo)
{
	pthread_mutex_lock(cur_philo->left_fork);
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time),MINT "has taken left fork" RESET);
	pthread_mutex_lock(cur_philo->right_fork);
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time),MINT "has taken right fork" RESET);
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time),MINT "is " GOLD "eating" RESET);
	usleep(cur_philo->data->time_to_eat * 1000);
	cur_philo->last_meal = ft_gettime();
	cur_philo->meals_eaten++;
	pthread_mutex_unlock(cur_philo->left_fork);
	pthread_mutex_unlock(cur_philo->right_fork);
}

static void	ft_sleep(t_philo *cur_philo)
{
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time),MINT "is " L_BLUE "sleeping" RESET);
	usleep(cur_philo->data->time_to_sleep * 1000);
}

static void	ft_think(t_philo *cur_philo)
{
	ft_display_logs(cur_philo, ft_timer(cur_philo->data->start_time),MINT "is " L_PURPLE "thinking" RESET);
}

static int	ft_die(t_philo *cur_philo)
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
		usleep(cur_philo->data->time_to_eat * 1000);
	while (1)
	{
		if (ft_die(cur_philo))
			return (NULL);
		ft_meal(cur_philo);
		ft_sleep(cur_philo);
		ft_think(cur_philo);
	}
	return (NULL);
}