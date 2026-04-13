#include "../inc/philo.h"

void	ft_data_display(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	printf(B_BLUE "\nSIMULATION SETTINGS\n\n" RESET);
	printf(MINT "nb_philo : " CORAL "[%d]\n" RESET, data->nb_philo);
	printf(MINT "time_to_die : " CORAL "[%d]\n" RESET, data->time_to_die);
	printf(MINT "time_to_eat : " CORAL "[%d]\n" RESET, data->time_to_eat);
	printf(MINT "time_to_sleep : " CORAL "[%d]\n" RESET, data->time_to_sleep);
	printf(MINT "must_eat : " CORAL "[%d]\n\n" RESET, data->must_eat);
	printf(B_BLUE "PHILO SETTINGS\n\n" RESET);
	i = 0;
	while (i < data->nb_philo)
	{
		printf(MINT "philo" CORAL "[%d]\n" RESET, data->philos[i].id);
		printf(MINT "last_meal : " CORAL "[%ld]\n" RESET,
				data->philos[i].last_meal);
		printf(MINT "meals_eaten : " CORAL "[%d]\n" RESET,
				data->philos[i].meals_eaten);
		j = 0;
		while (j < data->nb_philo)
		{
			if (data->philos[i].left_fork == &data->forks[j])
				printf(MINT "left_fork : " CORAL "[%d]\n" RESET, j);
			else if (data->philos[i].right_fork == &data->forks[j])
				printf(MINT "right_fork : " CORAL "[%d]\n" RESET, j);
			j++;
		}
		printf("\n");
		i++;
	}
}

static void	*ft_watch_routine(void *args)
{
	int		i;
	t_data	*data;
	int		dead;

	data = (t_data *)args;
	dead = 0;
	i = 0;
	while (!dead)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if ((data->philos[i].last_meal >= data->time_to_die) ||
				(data->philos[i].meals_eaten >= data->must_eat))
			{
				dead = 1;
			}
			i++;
		}
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (NULL);
}

pthread_t	*ft_monitoring(t_data *data)
{
	pthread_t *monitor = malloc(sizeof(pthread_t));
	pthread_create(monitor, NULL, ft_watch_routine, data);
	return (monitor);
}