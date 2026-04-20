#include "../inc/philo.h"

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
	ft_start_line(cur_philo->data->start_time);
	if ((cur_philo->id & 1) && cur_philo->data->nb_philo > 1)
		ft_waiting(cur_philo->data->time_to_eat / 2, cur_philo);
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