#include "../inc/philo.h"

static	int	ft_cron(void)
{
	static	long cron = 0;

	if (!cron)
		cron = ft_gettime();
	else if ((ft_gettime() - cron) < 10000)
		return 0;
	else
		cron = ft_gettime();
	return 1;
}

void	ft_data_display(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	if (!ft_cron())
		return ;
	pthread_mutex_lock(&data->print_mutex);
	printf(B_BLUE "\nSIMULATION SETTINGS\n\n" RESET);
	printf("nb_philo = " CORAL "= %d\n" RESET, data->nb_philo);
	printf("time_to_die = " CORAL "%d\n" RESET, data->time_to_die);
	printf("time_to_eat = " CORAL "%d\n" RESET, data->time_to_eat);
	printf("time_to_sleep = " CORAL "%d\n" RESET, data->time_to_sleep);
	printf("must_eat = " CORAL "= %d\n\n" RESET, data->must_eat);
	printf(B_BLUE "PHILO SETTINGS\n\n" RESET);
	i = 0;
	while (i < data->nb_philo)
	{
		printf(MINT "philo" ICE_BLUE "[%d]\n" RESET, data->philos[i].id);
		printf("last_meal = " CORAL "%ld\n" RESET,
				data->philos[i].last_meal);
		printf("meals_eaten = " CORAL "%d\n" RESET,
				data->philos[i].meals_eaten);
		j = 0;
		while (j < data->nb_philo)
		{
			if (data->philos[i].left_fork == &data->forks[j])
				printf("left_fork = " CORAL "%d\n" RESET, j);
			else if (data->philos[i].right_fork == &data->forks[j])
				printf("right_fork = " CORAL "%d\n" RESET, j);
			j++;
		}
		printf("\n");
		i++;
	}
	pthread_mutex_unlock(&data->print_mutex);
}

static void    ft_display_stats(t_philo *philo, char *stat,long value)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d %s %ls\n", philo->id, stat, value);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	*ft_watch_routine(void *args)
{
	int						i;
	t_data					*data;
	volatile __sig_atomic_t	stop_it;

	data = (t_data *)args;
	stop_it = 0;
	i = 0;
	while (!stop_it)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if ((data->philos[i].last_meal >= data->time_to_die) ||
				(data->philos[i].meals_eaten >= data->must_eat))
			{
				ft_display_stats(data->philo[i], "last meal = ", data->philo[i]);
				
				stop_it = 1;
			}
			i++;
		}
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	return (NULL);
}

void	ft_monitoring(t_data *data)
{
	pthread_create(&data->monitor, NULL, ft_watch_routine, data);
}