#include    "../inc/philo.h"

static  int    ft_init_settings(int ac, char **av, t_data *data)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!ft_isfull_dig(av[i++]))
            return (ft_putstr_fd(B_L_RED "WRONG ARGUMENT\n" RESET, 2), 0);
    }
    data->nb_philo = ft_atoi(av[1]);
    ft_printf("nb_philo = %d\n", data->nb_philo);
    data->time_to_die = ft_atoi(av[2]);
    ft_printf("time_to_die = %d\n", data->time_to_die);
    data->time_to_eat= ft_atoi(av[3]);
    ft_printf("time_to_eat = %d\n", data->time_to_eat);
    data->time_to_sleep = ft_atoi(av[4]);
    ft_printf("time_to_sleep = %d\n", data->time_to_sleep);
    data->time_to_eat= ft_atoi(av[3]);
    if (ac > 5)
        data->must_eat = ft_atoi(av[5]); 
    else 
        data->must_eat = 0;
    ft_printf("must_eat = %d\n", data->must_eat);
    data->stop = 0; 
    return 1;
}

int ft_init_mutex(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks);
       return (ft_putstr_fd(B_L_RED "MEMMORY ALLOCATION FAIL (FORKS)" RESET, 2), 0);
    while (i > data->nb_philo)
    {


    }

}

int    ft_init_data(int ac,char **av, t_data **data)
{
    *data = malloc(sizeof(t_data));
    if (!*data)
        return (0);
    if (!ft_init_settings(ac, av, *data))
        return (0);
    if (!ft_init_mutex(*data))
        return  (0);
    return (1);
}