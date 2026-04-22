#include "../inc/philo.h"

/*
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
				fprintf(dash, "left_fork = " CORAL "%d\n" RESET, j + 1);
			else if (data->philo[i].right_fork == &data->forks[j])
				fprintf(dash, "right_fork = " CORAL "%d\n" RESET, j + 1);
			j++;
		}
		fprintf(dash, "\n");
		i++;
	}
	fclose(dash);
}
*/

static	void    ft_display_end(t_philo *philo,long  time,char *logs)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n",time, philo->id, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

/*

static	int ft_died(t_data *data)
{
	int	i;
	long	last_meal;

	i = 0;
	last_meal = 0;
	while(i < data->nb_philo)
	{
		last_meal = data->philo[i].last_meal;
		if ((ft_duration(last_meal)) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			ft_display_end(&data->philo[i], ft_duration(data->start_time),BL_RED "died" RESET);
			return 1;
		}
		i++;
	}
	return 0;
}

static	int ft_satisfied(t_data *data)
{
	int	i;
	int	meals_eaten;


	i = 0;
	meals_eaten = 0;
	if (!data->must_eat)
		return 0;
	while(i < data->nb_philo)
	{	
		meals_eaten = data->philo[i].meals_eaten;
		if (meals_eaten < data->must_eat)
			break;
		if (i == (data->nb_philo - 1))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
		}
		i++;
	}
	return (i == data->nb_philo);
}

static void	*ft_watch_routine(void *args)
{
	t_data					*data;

	data = (t_data *)args;
	ft_start_line(data->start_time);
	while (1)		
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (ft_died(data) || ft_satisfied(data))		
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		usleep(1000);
	}
	return (NULL);
}
*/

static	int ft_died(t_data *data)
{
	int	i;
	long	last_meal;

	i = 0;
	last_meal = 0;
	while(i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		last_meal = data->philo[i].last_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		if ((ft_duration(last_meal)) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			ft_display_end(&data->philo[i], ft_duration(data->start_time),BL_RED "died" RESET);
			return 1;
		}
		i++;
	}
	return 0;
}

static	int ft_satisfied(t_data *data)
{
	int	i;
	int	meals_eaten;


	i = 0;
	meals_eaten = 0;
	if (!data->must_eat)
		return 0;
	while(i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		meals_eaten = data->philo[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_mutex);
		if (meals_eaten < data->must_eat)
			break;
		if (i == (data->nb_philo - 1))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);	
		}
		i++;
	}
	return (i == data->nb_philo);
}

static void	*ft_watch_routine(void *args)
{
	t_data					*data;

	data = (t_data *)args;
	ft_start_line(data->start_time);
	while (1)
	{
		if (ft_died(data) || ft_satisfied(data))		
			return (NULL);
	}
}

int	ft_monitoring(t_data *data)
{
	data->monitor = 0;
	if (pthread_create(&data->monitor, NULL, ft_watch_routine, data) != 0)
		return (ft_clean_exit(data), 0);
	return 1;
}