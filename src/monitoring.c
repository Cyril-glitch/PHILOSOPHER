#include "../inc/philo.h"

void	ft_data_display(t_data *data)
{
	int		i;
	int		j;
	FILE	*dash;

	dash = fopen("dashboard.txt", "w+");
	j = 0;
	fprintf(dash, B_BLUE "\nSIMULATION SETTINGS\n\n" RESET);
	fprintf(dash, "nb_philo = " CORAL "= %d\n" RESET, data->nb_philo);
	fprintf(dash, "time_to_die = " CORAL "%d\n" RESET, data->time_to_die);
	fprintf(dash, "time_to_eat = " CORAL "%d\n" RESET, data->time_to_eat);
	fprintf(dash, "time_to_sleep = " CORAL "%d\n" RESET, data->time_to_sleep);
	fprintf(dash, "must_eat = " CORAL "= %d\n\n" RESET, data->must_eat);
	fprintf(dash, B_BLUE "PHILO SETTINGS\n\n" RESET);
	i = 0;
	while (i < data->nb_philo)
	{
		fprintf(dash, MINT "philo" ICE_BLUE "[%d]\n" RESET, data->philo[i].id);
		fprintf(dash, "last_meal = " CORAL "%ld\n" RESET,
				data->philo[i].last_meal);
		fprintf(dash, "meals_eaten = " CORAL "%d\n" RESET,
				data->philo[i].meals_eaten);
		j = 0;
		while (j < data->nb_philo)
		{
			if (data->philo[i].left_fork == &data->forks[j])
				fprintf(dash, "left_fork = " CORAL "%d\n" RESET, j);
			else if (data->philo[i].right_fork == &data->forks[j])
				fprintf(dash, "right_fork = " CORAL "%d\n" RESET, j);
			j++;
		}
		fprintf(dash, "\n");
		i++;
	}
	fclose(dash);
}

static	int ft_ending(t_philo cur_philo)
{
	if ((ft_gettime() - cur_philo.last_meal) > cur_philo.data->time_to_die)
	{
		ft_display_logs(&cur_philo, 0,BL_RED "died" RESET);
		return 1;
	}
	if (cur_philo.meals_eaten >= cur_philo.data->must_eat)
	{
		ft_display_logs(&cur_philo, 0,BL_RED "finish" RESET);
		return 1;
	}
	return (0);
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
		while (i < data->nb_philo && !stop_it)
		{	
			if (ft_ending(data->philo[i]))
			{
				stop_it = 1;
			}
			i++;
		}
	}
	data->stop = 1;
	return (NULL);
}

void	ft_monitoring(t_data *data)
{
	pthread_create(&data->monitor, NULL, ft_watch_routine, data);
}