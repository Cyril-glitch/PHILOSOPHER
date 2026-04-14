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
	return (1);
}

static int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (ft_putstr_fd(BL_RED "MEMMORY ALLOCATION FAIL (FORKS)" RESET,
				2), 0);
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);

	return (1);
}

static	int	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (ft_putstr_fd(BL_RED "MEMMORY ALLOCATION FAIL (PHILOS)" RESET,
				2), 0);
	while(i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data; 
		pthread_create(&data->philo[i].thread, NULL, ft_routine, &data->philo[i]);
		data->philo[i].last_meal = 0;
		data->philo[i].meals_eaten = 0;
		if (i == 0)
			data->philo[i].left_fork = &data->forks[data->nb_philo - 1];
		else
			data->philo[i].left_fork = &data->forks[i - 1];
		if (i + 1 == data->nb_philo)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
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
	(*data)->start_time = ft_gettime();
	if (!ft_init_philo(*data))
		return (0);
	return (1);
}