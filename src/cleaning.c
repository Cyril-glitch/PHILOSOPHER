#include    "../inc/philo.h"

void ft_thread_join(t_data *data)
{
    int i;

    i = 0; 
    if (data->monitor)
        pthread_join(data->monitor, NULL);
    while (i < data->nb_philo)
    {
        if (data->philo[i].thread)
            pthread_join(data->philo[i].thread, NULL); 
        i++;
    }
}

void    ft_mutex_destroy(t_data *data, int to_del)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        if (to_del--)
        pthread_mutex_destroy(&data->forks[i++]);
    }
    if (to_del--)
        pthread_mutex_destroy(&data->stop_mutex);
    if (to_del--)
        pthread_mutex_destroy(&data->print_mutex);
    if (to_del--)
        pthread_mutex_destroy(&data->meal_mutex);
}

void    ft_clean_exit(t_data *data)
{
    ft_mutex_destroy(data, data->nb_philo);
    ft_thread_join(data);
    if (data->forks)
        free(data->forks);
    if (data->philo)
        free(data->philo);
    free(data);
}