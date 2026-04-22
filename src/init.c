#include "../inc/philo.h"


static int	ft_init_settings(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isfull_dig(av[i++]))
			return (ft_putstr_fd(BL_RED "WRONG ARGUMENT\n" RESET, 2), 0);
	}
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_eat = ft_atoi(av[3]);
	if (ac > 5)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = 0;
	data->stop = 0;
    data->start_time = 0;
	if (ft_overflow(data))
		return 0;
	return (1);
}

static int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data);
		return (ft_putstr_fd(BL_RED "MEMMORY ALLOCATION FAIL (FORKS)" RESET,
				2), 0);
	}
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_mutex_destroy(data, i + 1, 0), 0);
		i++;
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (ft_mutex_destroy(data ,i, 1), 0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_mutex_destroy(data ,i, 2), 0);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (ft_mutex_destroy(data ,i, 3), 0);
	return (1);
}

static	int	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
	{
    	ft_mutex_destroy(data, 0,3);
		free(data);
		return (ft_putstr_fd(BL_RED "MEMMORY ALLOCATION FAIL (PHILOS)" RESET,
				2), 0);
	}
	while(i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data; 
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meals_eaten = 0;	
		data->philo[i].right_fork = &data->forks[(i + data->nb_philo - 1) % data->nb_philo];	
		if (data->nb_philo == 1)
			break;
		data->philo[i].left_fork = &data->forks[i];
		i++;
	}
	return 1;
}

int	ft_start_simulation(t_data *data)
{
	int	i;
	void *routine;

	i = 0;
	if (data->nb_philo == 1)
		routine = ft_solo_routine;
	else 
		routine = ft_routine;	
	while(i < data->nb_philo)
	{
		data->philo[i].thread = 0;
		if ((pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i])) != 0)
		{
			ft_clean_exit(data);
			return 0;
		}
		i++;
	}
	return 1;
}

int	ft_init_simulation(int ac, char **av, t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	if (!ft_init_settings(ac, av, *data))
		return (0);
	if (!ft_init_mutex(*data))
		return (0);
	(*data)->start_time = ft_gettime() + 300;
	if (!ft_init_philo(*data))
		return (0);
	return (1);
}